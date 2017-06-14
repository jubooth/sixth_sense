package com.adafruit.bluefruit.le.connect.app;

import android.content.Intent;
import android.graphics.Color;
import android.os.Bundle;
import android.support.v4.app.FragmentActivity;

import com.adafruit.bluefruit.le.connect.R;
import com.google.android.gms.maps.CameraUpdateFactory;
import com.google.android.gms.maps.GoogleMap;
import com.google.android.gms.maps.OnMapReadyCallback;
import com.google.android.gms.maps.SupportMapFragment;
import com.google.android.gms.maps.model.LatLng;
import com.google.android.gms.maps.model.MarkerOptions;
import com.google.android.gms.maps.model.Polyline;
import com.google.android.gms.maps.model.PolylineOptions;

public class MapActivity extends FragmentActivity implements OnMapReadyCallback {

    private GoogleMap mMap;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_map);
        SupportMapFragment mapFragment = (SupportMapFragment) getSupportFragmentManager()
                .findFragmentById(R.id.map);
        mapFragment.getMapAsync(this);
    }

    @Override
    public void onMapReady(GoogleMap googleMap) {
        mMap = googleMap;

        Intent intent = getIntent();
        double lat = intent.getDoubleExtra(GPSNavigationActivity.EXTRA_LAT,0);
        double lng = intent.getDoubleExtra(GPSNavigationActivity.EXTRA_LNG,0);
        //double lats[] = intent.getDoubleArrayExtra(GPSNavigationActivity.EXTRA_LATS);
        //double lngs[] = intent.getDoubleArrayExtra(GPSNavigationActivity.EXTRA_LNGS);


        //LatLng origin = new LatLng(lat,lng);

        // Add a marker in Sydney, Australia, and move the camera.
        //LatLng sydney = new LatLng(-34, 151);
        Polyline line = mMap.addPolyline(new PolylineOptions()
                .add(new LatLng(51.498017, -0.176456), new LatLng(51.497774, -0.179423), new LatLng(51.500074, -0.179939), new LatLng(51.500151, -0.179121),  new LatLng(51.500597, -0.17818),  new LatLng(51.500518, -0.177317))
                .width(5)
                .color(Color.RED));
        mMap.moveCamera(CameraUpdateFactory.newLatLng(new LatLng(51.498017, -0.176456)));
        mMap.setMinZoomPreference(15);
        //mMap.addMarker(new MarkerOptions().position(origin).title("Start"));
        //mMap.moveCamera(CameraUpdateFactory.newLatLng(origin));
    }
}