package com.example.liang.gpio_demo;

import android.app.Activity;
import android.os.Bundle;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;
import android.widget.TextView;

public class MainActivity extends Activity implements OnClickListener {

    private TextView metextview;
    private Button mybutton1;
    private Button mybutton2;

    private Button mybutton3;
    private Gpio megpio=null;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        metextview=(TextView)findViewById(R.id.textView);
        mybutton1=(Button)findViewById(R.id.button);
        mybutton1.setOnClickListener(this);
        mybutton2=(Button)findViewById(R.id.button2);
        mybutton2.setOnClickListener(this);
        mybutton3=(Button)findViewById(R.id.button3);
        mybutton3.setOnClickListener(this);
        megpio=new Gpio();
    }
    public void onClick(View v) {
        switch(v.getId()){
            case R.id.button:
                //metextview.setText("init pjsip is ok");
                //megpio.Init_GPIO("ssaa",1);
                if(megpio.Get_GPIO("PI5",1,1)==1){
                    metextview.setText("get Gpio high");
                }else{
                    metextview.setText("get Gpio low");
                }
                System.out.println("Get the words: " + "ok");
                break;
            case R.id.button2:
                metextview.setText("init pjsip is ok");
                megpio.Init_GPIO("PI5",1);
               // megpio.Get_GPIO("PI5",1,1);
                System.out.println("Get the words: " + "ok");
                break;
            case R.id.button3:
                metextview.setText("init pjsip is ok");
                //megpio.Init_GPIO("ssaa",1);
                megpio.Set_GPIO("PI9",1,1);
                System.out.println("Get the words: " + "ok");
                break;
            default:
                break;
        }

    }
}
