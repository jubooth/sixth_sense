package com.example.directions;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.TextView;

import com.google.maps.DirectionsApi;
import com.google.maps.GeoApiContext;
import com.google.maps.model.DirectionsResult;
import com.google.maps.model.TravelMode;

import static java.lang.Math.PI;
import static java.lang.Math.abs;
import static java.lang.Math.atan;
import static java.lang.Math.sqrt;

public class MainActivity extends AppCompatActivity {

    public String travelMode = "walking";
    public String origin = "Imperial College London, UK";
    public String destination = "Royal Albert Hall, London, UK";
    GeoApiContext context = new GeoApiContext().setApiKey("AIzaSyC7HmJjEPcHOl9G9f6BkYgsXHmmE0E-w7c");
    public int step = 0;
    public int leg = 0;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        TextView textView = (TextView) findViewById(R.id.textView);
        textView.setText("Hi Ju!");

        TextView textView2 = (TextView) findViewById(R.id.textView2);
        textView2.setText("Welcome");
    }

    public void onGo(View view) {
        String output, output2, output4;
        try {
            DirectionsResult result;
            if(travelMode == "cycling"){
                result = DirectionsApi.newRequest(context)
                        .mode(TravelMode.BICYCLING)
                        .origin(origin)
                        .destination(destination).await();
            }
            else{
                result = DirectionsApi.newRequest(context)
                        .mode(TravelMode.WALKING)
                        .origin(origin)
                        .destination(destination).await();
            }
            output = result.routes[0].summary;
            String str = result.routes[0].legs[leg].steps[step].htmlInstructions;
            int boldStart = str.indexOf("<b>");
            int directionStart = boldStart + 3;
            int directionEnd = str.indexOf("</b>");
            String direction = str.substring(directionStart, directionEnd);
            String degree = str.substring(0, boldStart-1);

            if(degree.equals("Head")){
                switch (direction){
                    case "north":
                        output4 = "forward";
                        break;
                    case "north east":
                        output4 = "forward right";
                        break;
                    case "east":
                        output4 = "right";
                        break;
                    case "south east":
                        output4 = "back right";
                        break;
                    case "south":
                        output4 = "back";
                        break;
                    case "south west":
                        output4 = "back left";
                        break;
                    case "west":
                        output4 = "left";
                        break;
                    case "north west":
                        output4 = "forward left";
                        break;
                    default:
                        output4 = "nothing";
                        break;
                }
            }
            else if(degree.equals("Slight")){
                switch (direction){
                    case "right":
                        output4 = "forward right";
                        break;
                    case "left":
                        output4 = "forward left";
                        break;
                    default:
                        output4 = "forward";
                        break;
                }
            }
            else if(degree.equals("Turn")){
                switch (direction){
                    case "right":
                        output4 = "right";
                        break;
                    case "left":
                        output4 = "left";
                        break;
                    default:
                        output4 = "forward";
                        break;
                }
            }
            else{
                output4 = "forward";
            }

            output2 = result.routes[0].legs[leg].steps[step].endLocation.toString();
            step++;

            TextView textView2 = (TextView) findViewById(R.id.textView2);
            textView2.setText(output2);
            TextView textView4 = (TextView) findViewById(R.id.textView4);
            textView4.setText(output4);
        }
        catch (Exception e){
            output = e.toString();
        }

        TextView textView = (TextView) findViewById(R.id.textView);
        textView.setText(output);
    }

    public void onWalking(View view) {
        travelMode = "walking";
    }

    public void onCycling(View view) {
        travelMode = "cycling";
    }
}
