package com.example.liang.gpio_demo;

import android.app.Activity;
import android.os.Bundle;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;
import android.widget.TextView;

public class MainActivity extends Activity implements OnClickListener {

    private TextView metextview;
    private Button mybutton;
    private Gpio megpio=null;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        metextview=(TextView)findViewById(R.id.textView);
        mybutton=(Button)findViewById(R.id.button);
        mybutton.setOnClickListener(this);
        megpio=new Gpio();
    }
    public void onClick(View v) {
        switch(v.getId()){
            case R.id.button:
                metextview.setText("init pjsip is ok");
                megpio.Init_GPIO("ssaa",1);
                System.out.println("Get the words: " + "ok");
            default:
                break;
        }

    }
}
