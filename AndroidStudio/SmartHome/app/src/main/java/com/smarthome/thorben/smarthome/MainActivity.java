package com.smarthome.thorben.smarthome;

import android.content.Intent;
import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.view.View;
import android.widget.GridLayout;
import android.widget.TextView;

public class MainActivity extends AppCompatActivity {

    GridLayout mainGrid;
    Intent startHomeActivity;
    private TextView title;


    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        title = (TextView) findViewById(R.id.textGrid);
        startHomeActivity = new Intent(this, HomeActivity.class);
        //startStatisticsActivity = new Intent(this,StatisticsActivity.class);
        //startControllerActivity = new Intent(this,ControllerActivity.class);
        //startLEDActivity = new Intent(this,LEDActivity.class);


        mainGrid = (GridLayout) findViewById(R.id.grid);
        setSingleEvent(mainGrid);
    }


    private void setSingleEvent(GridLayout mainGrid) {
        mainGrid.getChildAt(0).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                startActivity(startHomeActivity);
            }
        });
        mainGrid.getChildAt(1).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                title.setText("LED-Matrix");
            }
        });
        mainGrid.getChildAt(2).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                title.setText("Steuerung");
            }
        });
        mainGrid.getChildAt(3).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                title.setText("Statistiken");
            }
        });

    }
}
