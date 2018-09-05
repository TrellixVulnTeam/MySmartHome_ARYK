package com.smarthome.thorben.smarthome;

import android.content.Intent;
import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.view.View;
import android.widget.GridLayout;
import android.widget.TextView;
import android.widget.Toast;

public class MainActivity extends AppCompatActivity {

    GridLayout mainGrid;
    Intent startHomeActivity,startLEDMatrixActivity;
    private TextView title;


    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        title = (TextView) findViewById(R.id.textGrid);
        startHomeActivity = new Intent(this, HomeActivity.class);
        startLEDMatrixActivity = new Intent(this, LEDMatrixActivity.class);

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
                startActivity(startLEDMatrixActivity);
            }
        });
        mainGrid.getChildAt(2).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                //Steuerung
                Toast.makeText(MainActivity.this, "controlling coming soon!", Toast.LENGTH_LONG).show();
            }
        });
        mainGrid.getChildAt(3).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                //Statistiken
                Toast.makeText(MainActivity.this, "statistics coming soon!", Toast.LENGTH_LONG).show();
            }
        });

    }
}
