package com.example.directions;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.TextView;

import com.google.maps.DirectionsApi;
import com.google.maps.GeoApiContext;
import com.google.maps.model.DirectionsResult;

public class MainActivity extends AppCompatActivity {

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
        GeoApiContext context = new GeoApiContext().setApiKey("AIzaSyC7HmJjEPcHOl9G9f6BkYgsXHmmE0E-w7c");
        String output, output2, output3;
        try {
            DirectionsResult result = DirectionsApi.getDirections(context, "Imperial College London, UK", "Royal Albert Hall, London, UK").await();
            output = result.routes[0].summary;
            output2 = result.routes[0].legs[0].startLocation.toString();
            output3 = result.routes[0].legs[0].endLocation.toString();

            TextView textView2 = (TextView) findViewById(R.id.textView2);
            textView2.setText(output2);
            TextView textView3 = (TextView) findViewById(R.id.textView3);
            textView3.setText(output3);
        }
        catch (Exception e){
            output = e.toString();
        }
        TextView textView = (TextView) findViewById(R.id.textView);
        textView.setText(output);
    }
}
