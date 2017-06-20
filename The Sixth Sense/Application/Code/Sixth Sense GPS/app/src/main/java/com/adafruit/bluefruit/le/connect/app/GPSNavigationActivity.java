package com.adafruit.bluefruit.le.connect.app;

import android.Manifest;
import android.content.Context;
import android.content.DialogInterface;
import android.content.Intent;
import android.content.pm.PackageManager;
import android.location.Location;
import android.location.LocationListener;
import android.location.LocationManager;
import android.os.Bundle;
import android.os.Parcelable;
import android.provider.Settings;
import android.support.v4.app.ActivityCompat;
import android.support.v7.app.AlertDialog;
import android.view.View;
import android.widget.EditText;
import android.widget.TextView;

import com.adafruit.bluefruit.le.connect.R;
import com.adafruit.bluefruit.le.connect.ble.BleManager;
import com.google.android.gms.maps.CameraUpdateFactory;
import com.google.android.gms.maps.GoogleMap;
import com.google.android.gms.maps.MapFragment;
import com.google.android.gms.maps.MapView;
import com.google.android.gms.maps.model.MarkerOptions;
import com.google.maps.DirectionsApi;
import com.google.maps.GeoApiContext;
import com.google.maps.model.DirectionsResult;
import com.google.maps.model.DirectionsStep;
import com.google.maps.model.EncodedPolyline;
import com.google.maps.model.LatLng;
import com.google.maps.model.TravelMode;

import java.util.List;

import static java.lang.Math.sqrt;

public class GPSNavigationActivity extends UartInterfaceActivity {

    public String travelMode = "walking";
    public String origin = "Imperial College London, UK";
    public String destination = "The Albert Memorial, London, UK";
    public LatLng start = new LatLng(51.49801369999999, -0.17646930000000793);
    public LatLng instrEnd = new LatLng(0,0);
    GeoApiContext context = new GeoApiContext().setApiKey("AIzaSyC7HmJjEPcHOl9G9f6BkYgsXHmmE0E-w7c");
    public int step = 0;
    public int leg = 0;
    DirectionsStep directions[];

    public static final String EXTRA_LAT = "0";
    public static final String EXTRA_LNG = "0";
    public static final String EXTRA_LATS = "0";
    public static final String EXTRA_LNGS = "0";

    LocationManager locationManager;
    double longitudeGPS, latitudeGPS;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_gpsnavigation);

        mBleManager = BleManager.getInstance(this);

        onServicesDiscovered();

        locationManager = (LocationManager) getSystemService(Context.LOCATION_SERVICE);
    }

    @Override
    public void onResume() {
        super.onResume();

        // Setup listeners
        mBleManager.setBleListener(this);

    }

    @Override
    public void onServicesDiscovered() {
        super.onServicesDiscovered();
        enableRxNotifications();
    }

    public void onUpdateDestination(View view) {
        EditText editText = (EditText) findViewById(R.id.editText2);
        String message = editText.getText().toString();
        destination = message + ", London, UK";
        TextView textView = (TextView) findViewById(R.id.textView);
        textView.setText(destination);
        step = 0;
        LatLng gps = updateGPSLocation();
        TextView textView2 = (TextView) findViewById(R.id.textView2);
        if((gps.lat == 0) && (gps.lng == 0)){
            textView.setText("no GPS location available");
            textView2.setText("no GPS location available");
        }
        else{
            textView2.setText(gps.toString());
            start = gps;
        }
        try {
            DirectionsResult result;
            if (travelMode == "cycling") {
                result = DirectionsApi.newRequest(context)
                        .mode(TravelMode.BICYCLING)
                        .origin(start)
                        .destination(destination).await();
            } else {
                result = DirectionsApi.newRequest(context)
                        .mode(TravelMode.WALKING)
                        .origin(start)
                        .destination(destination).await();
            }

            directions = result.routes[0].legs[0].steps.clone();
            instrEnd = directions[0].endLocation;

        } catch(Exception e){

        }
    }

    public void onGo(View view) {
        String output = "forwards";
        String output2, output4;
        LatLng gps;
        char send;
        while(output != "destination reached") {
            gps = updateGPSLocation();
            TextView textView2 = (TextView) findViewById(R.id.textView2);
            textView2.setText(gps.toString());
            double closeLat = instrEnd.lat - gps.lat;
            double closeLng = instrEnd.lng - gps.lng;
            double dist = sqrt((closeLat*closeLat)+(closeLng*closeLng));
            if(dist < 0.0003) {
                try {
                    /*DirectionsResult result;
                    if (travelMode == "cycling") {
                        result = DirectionsApi.newRequest(context)
                                .mode(TravelMode.BICYCLING)
                                .origin(origin)
                                .destination(destination).await();
                    } else {
                        result = DirectionsApi.newRequest(context)
                                .mode(TravelMode.WALKING)
                                .origin(origin)
                                .destination(destination).await();
                    }

                    output = result.routes[0].summary;
                    String str = result.routes[0].legs[leg].steps[step].htmlInstructions;*/

                    String str = directions[step].htmlInstructions;
                    int boldStart = str.indexOf("<b>");
                    int directionStart = boldStart + 3;
                    int directionEnd = str.indexOf("</b>");
                    String direction = str.substring(directionStart, directionEnd);
                    String degree = str.substring(0, boldStart - 1);

                    if (degree.equals("Head")) {
                        switch (direction) {
                            case "north":
                                output4 = "forward";
                                send = '1';
                                break;
                            case "north east":
                                output4 = "forward right";
                                send = '2';
                                break;
                            case "east":
                                output4 = "right";
                                send = '3';
                                break;
                            case "south east":
                                output4 = "back right";
                                send = '4';
                                break;
                            case "south":
                                output4 = "back";
                                send = '5';
                                break;
                            case "south west":
                                output4 = "back left";
                                send = '6';
                                break;
                            case "west":
                                output4 = "left";
                                send = '7';
                                break;
                            case "north west":
                                output4 = "forward left";
                                send = '8';
                                break;
                            default:
                                output4 = "nothing";
                                send = '9';
                                break;
                        }
                    } else if (degree.equals("Slight")) {
                        switch (direction) {
                            case "right":
                                output4 = "forward right";
                                send = '2';
                                break;
                            case "left":
                                output4 = "forward left";
                                send = '8';
                                break;
                            default:
                                output4 = "forward";
                                send = '1';
                                break;
                        }
                    } else if (degree.equals("Turn")) {
                        switch (direction) {
                            case "right":
                                output4 = "right";
                                send = '3';
                                break;
                            case "left":
                                output4 = "left";
                                send = '7';
                                break;
                            default:
                                output4 = "forward";
                                send = '1';
                                break;
                        }
                    } else if (degree.equals("Continue")) {
                        output4 = "forward";
                        send = '1';
                    } else {
                        output4 = "forward";
                        send = '1';
                    }

                    step++;
                    instrEnd = directions[step].endLocation;
                    TextView textView9 = (TextView) findViewById(R.id.textView9);
                    textView9.setText(instrEnd.toString());
                    /*output2 = result.routes[0].legs[leg].steps[step].endLocation.toString();
                    step++;

                    TextView textView2 = (TextView) findViewById(R.id.textView2);
                    textView2.setText(output2);*/

                } catch (Exception e) {
                    output = "destination reached";
                    output4 = "warning";
                    send = '0';
                }

                byte data[] = new byte[1];
                data[0] = (byte) send;
                sendData(data);

                /*TextView textView = (TextView) findViewById(R.id.textView);
                textView.setText(output);*/
                TextView textView7 = (TextView) findViewById(R.id.textView7);
                textView7.setText(output4);
            }
        }
    }

    public void onWalking(View view) {
        travelMode = "walking";
    }

    public void onCycling(View view) {
        travelMode = "cycling";
    }

    private boolean checkLocation() {
        if (!isLocationEnabled())
            showAlert();
        return isLocationEnabled();
    }

    private void showAlert() {
        final AlertDialog.Builder dialog = new AlertDialog.Builder(this);
        dialog.setTitle("Enable Location")
                .setMessage("Your Locations Settings is set to 'Off'.\nPlease Enable Location to " +
                        "use this app")
                .setPositiveButton("OK", new DialogInterface.OnClickListener() {
                    @Override
                    public void onClick(DialogInterface paramDialogInterface, int paramInt) {
                    }
                })
                .setNegativeButton("Cancel", new DialogInterface.OnClickListener() {
                    @Override
                    public void onClick(DialogInterface paramDialogInterface, int paramInt) {
                    }
                });
        dialog.show();
    }

    private boolean isLocationEnabled() {
        return locationManager.isProviderEnabled(LocationManager.GPS_PROVIDER) ||
                locationManager.isProviderEnabled(LocationManager.NETWORK_PROVIDER);
    }

    public LatLng updateGPSLocation() {
        LatLng loc = new LatLng(0,0);
        if (!checkLocation())
            return loc;
        if (ActivityCompat.checkSelfPermission(this, Manifest.permission.ACCESS_FINE_LOCATION) != PackageManager.PERMISSION_GRANTED && ActivityCompat.checkSelfPermission(this, Manifest.permission.ACCESS_COARSE_LOCATION) != PackageManager.PERMISSION_GRANTED) {
            // TODO: Consider calling
            //    ActivityCompat#requestPermissions
            // here to request the missing permissions, and then overriding
            //   public void onRequestPermissionsResult(int requestCode, String[] permissions,
            //                                          int[] grantResults)
            // to handle the case where the user grants the permission. See the documentation
            // for ActivityCompat#requestPermissions for more details.
            System.out.println("no permission");
            return loc;
        }
        locationManager.requestLocationUpdates(LocationManager.GPS_PROVIDER, 2 * 60 * 1000, 10, locationListenerGPS);
        System.out.println("requested");
        Location location = locationManager.getLastKnownLocation(LocationManager.GPS_PROVIDER);
        if(location != null) {
            longitudeGPS = location.getLongitude();
            latitudeGPS = location.getLatitude();
            loc.lng = longitudeGPS;
            loc.lat = latitudeGPS;

            String output2 = longitudeGPS + ", " + latitudeGPS;
           /* TextView textView2 = (TextView) findViewById(R.id.textView2);
            textView2.setText(output2);
            System.out.println(longitudeGPS);
            System.out.println(latitudeGPS);*/
            return loc;
        }
        else{
            /*TextView textView2 = (TextView) findViewById(R.id.textView2);
            textView2.setText("location is null");
            System.out.println("location is null");*/
            return loc;
        }
    }

    public void onCheckRoute(View view){
        Intent intent = new Intent(this, MapActivity.class);
        try {
            EncodedPolyline route = directions[0].polyline;
            LatLng point;
            int size = route.decodePath().size();
            double lats[] = new double[size];
            double lngs[] = new double[size];
            for (int i = 0; i < size; i++) {
                point = route.decodePath().get(i);
                lats[i] = point.lat;
                lngs[i] = point.lng;
            }
            intent.putExtra(EXTRA_LAT, start.lat);
            intent.putExtra(EXTRA_LNG, start.lng);
            //intent.putExtra(EXTRA_LATS, lats);
            //intent.putExtra(EXTRA_LNGS, lngs);
        }
        catch(Exception e){
            intent.putExtra(EXTRA_LAT, start.lat);
            intent.putExtra(EXTRA_LNG, start.lng);
        }
        startActivity(intent);
    }

    private final LocationListener locationListenerGPS = new LocationListener() {
        @Override
        public void onLocationChanged(Location location) {
            longitudeGPS = location.getLongitude();
            latitudeGPS = location.getLatitude();
            System.out.println(longitudeGPS);
            System.out.println(latitudeGPS);
        }

        @Override
        public void onStatusChanged(String provider, int status, Bundle extras) {

        }

        @Override
        public void onProviderEnabled(String provider) {

        }

        @Override
        public void onProviderDisabled(String provider) {

        }
    };

}
