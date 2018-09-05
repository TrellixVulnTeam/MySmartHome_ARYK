package com.smarthome.thorben.smarthome;

import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.view.View;
import android.widget.Button;
import android.widget.CompoundButton;
import android.widget.EditText;
import android.widget.Toast;
import android.widget.ToggleButton;

import org.eclipse.paho.android.service.MqttAndroidClient;
import org.eclipse.paho.client.mqttv3.IMqttActionListener;
import org.eclipse.paho.client.mqttv3.IMqttDeliveryToken;
import org.eclipse.paho.client.mqttv3.IMqttToken;
import org.eclipse.paho.client.mqttv3.MqttCallback;
import org.eclipse.paho.client.mqttv3.MqttClient;
import org.eclipse.paho.client.mqttv3.MqttException;
import org.eclipse.paho.client.mqttv3.MqttMessage;

import java.io.UnsupportedEncodingException;

public class LEDMatrixActivity extends AppCompatActivity implements View.OnClickListener {

    private MqttAndroidClient client;
    private Button button;
    private EditText editText;
    private String mode = "Uhrzeit";
    private String status = "An";
    private ToggleButton toggle_status,toggle_mode;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_ledmatrix);

        toggle_mode = (ToggleButton) findViewById(R.id.toggleButtonMode);
        toggle_mode.setOnCheckedChangeListener(toggleListenerMode);

        toggle_status = (ToggleButton) findViewById(R.id.toggleButtonStatus);
        toggle_status.setOnCheckedChangeListener(toggleListenerStatus);

        button = (Button) findViewById(R.id.buttonLED);
        button.setOnClickListener(this);
        editText = (EditText) findViewById(R.id.editTextLED);

        setStringSendInvisible();

        String clientId = MqttClient.generateClientId();
        client =
                new MqttAndroidClient(this.getApplicationContext(), "tcp://192.168.178.102:1883",
                        clientId);

        try {
            IMqttToken token;
            token = client.connect();
            token.setActionCallback(new IMqttActionListener() {
                @Override
                public void onSuccess(IMqttToken asyncActionToken) {
                    // We are connected
                    Toast.makeText(LEDMatrixActivity.this,"Verbunden!",Toast.LENGTH_LONG).show();

                    setSubscription("ack_status");
                    setSubscription("ack_mode");

                    //information request to led-matrix to set togglebuttons accordingly
                    String topic = "info_led";
                    String payload = "0"; // no need for payload
                    byte[] encodedPayload = new byte[0];

                    try {
                        encodedPayload = payload.getBytes("UTF-8");
                        MqttMessage message = new MqttMessage(encodedPayload);
                        message.setRetained(true);
                        client.publish(topic, message);
                    } catch (UnsupportedEncodingException | MqttException e) {
                        e.printStackTrace();
                    }

                }

                @Override
                public void onFailure(IMqttToken asyncActionToken, Throwable exception) {
                    // Something went wrong e.g. connection timeout or firewall problems
                    Toast.makeText(LEDMatrixActivity.this,"Verbinden fehlgeschlagen!",Toast.LENGTH_LONG).show();
                }
            });
        } catch (MqttException e) {
            e.printStackTrace();
        }

        client.setCallback(new MqttCallback() {
            @Override
            public void connectionLost(Throwable cause) {

            }

            @Override
            public void messageArrived(String topic, MqttMessage message) throws Exception {
                if (topic.equals("ack_mode")) {
                    if(new String(message.getPayload()).equals("S")){
                        mode = "Text";
                        toggle_mode.setChecked(true);
                    }else if(new String(message.getPayload()).equals("T")){
                        mode = "Uhrzeit";
                        toggle_mode.setChecked(false);
                    }
                }else if (topic.equals("ack_status")) {
                    if(new String(message.getPayload()).equals("X")){ // off
                        status = "Aus";
                        toggle_status.setChecked(true);
                    }else if(new String(message.getPayload()).equals("Y")){ // on
                        status = "An";
                        toggle_status.setChecked(false);

                    }
                }

            }

            @Override
            public void deliveryComplete(IMqttDeliveryToken token) {

            }
        });

    }

    @Override
    public void onClick(View v){
        String topic = "msg_led";
        String payload = editText.getText().toString();
        editText.getText().clear();
        byte[] encodedPayload = new byte[0];

        try {
            encodedPayload = payload.getBytes("UTF-8");
            MqttMessage message = new MqttMessage(encodedPayload);
            message.setRetained(true);
            client.publish(topic, message);
        } catch (UnsupportedEncodingException | MqttException e) {
            e.printStackTrace();
        }
    }

    private void setSubscription(String topic){
        try{
            client.subscribe(topic,0);
        }catch(MqttException e){
            e.printStackTrace();
        }
    }

    private void setStringSendVisible(){
        button.setVisibility(View.VISIBLE);
        editText.setVisibility(View.VISIBLE);
    }

    private void setStringSendInvisible(){
        button.setVisibility(View.GONE);
        editText.setVisibility(View.GONE);
    }

    CompoundButton.OnCheckedChangeListener toggleListenerMode = new CompoundButton.OnCheckedChangeListener() {

        public void onCheckedChanged(CompoundButton v, boolean isChecked) {
            String topic = "mode_led";
            String payload = "";

            byte[] encodedPayload = new byte[0];

            if (isChecked) {
                try {
                    payload = "S";
                    encodedPayload = payload.getBytes("UTF-8");
                    MqttMessage message = new MqttMessage(encodedPayload);
                    message.setRetained(true);
                    client.publish(topic, message);
                    mode = "Text";
                    if(status.equals("An")) {
                        setStringSendVisible();
                    }
                } catch (UnsupportedEncodingException | MqttException e) {
                    e.printStackTrace();
                }

            } else {
                try {
                    payload = "T";
                    encodedPayload = payload.getBytes("UTF-8");
                    MqttMessage message = new MqttMessage(encodedPayload);
                    message.setRetained(true);
                    client.publish(topic, message);
                    mode = "Uhrzeit";
                    setStringSendInvisible();
                } catch (UnsupportedEncodingException | MqttException e) {
                    e.printStackTrace();
                }
            }
    }};

    CompoundButton.OnCheckedChangeListener toggleListenerStatus = new CompoundButton.OnCheckedChangeListener() {

        public void onCheckedChanged(CompoundButton v, boolean isChecked) {
            String topic = "mode_led";
            String payload = "";

            byte[] encodedPayload = new byte[0];

            if (isChecked) {
                try {
                    payload = "X";
                    encodedPayload = payload.getBytes("UTF-8");
                    MqttMessage message = new MqttMessage(encodedPayload);
                    message.setRetained(true);
                    client.publish(topic, message);
                    status = "Aus";
                    setStringSendInvisible();
                } catch (UnsupportedEncodingException | MqttException e) {
                    e.printStackTrace();
                }

            } else {
                try {
                    payload = "Y";
                    encodedPayload = payload.getBytes("UTF-8");
                    MqttMessage message = new MqttMessage(encodedPayload);
                    message.setRetained(true);
                    client.publish(topic, message);
                    status = "An";
                    if(mode.equals("Uhrzeit")){
                        setStringSendInvisible();
                    }else{
                        setStringSendVisible();
                    }
                } catch (UnsupportedEncodingException | MqttException e) {
                    e.printStackTrace();
                }
            }
    }};
}