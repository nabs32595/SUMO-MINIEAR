void forward(){
  right_forward ();
  left_forward ();
}

void backward(){
  left_backward ();
  right_backward ();
}

void turn_left(){
  right_forward ();
  left_backward ();
  delay(300);
}

void turn_right(){
  right_backward ();
  left_forward ();
  delay(300);
}


void round_left(){
  right_forward ();
  left_backward ();
}

void Stop(){
    analogWrite(right_LPWM_Output, 0);
    analogWrite(right_RPWM_Output, 0);
}


void right_forward (){
    analogWrite(right_LPWM_Output, 0);
    analogWrite(right_RPWM_Output, 255);
}

void left_forward (){
    analogWrite(left_RPWM_Output, 255);
    analogWrite(left_LPWM_Output, 0);
}


void right_backward (){
    analogWrite(right_LPWM_Output, 255);
    analogWrite(right_RPWM_Output, 0);
}

void left_backward (){
    analogWrite(left_RPWM_Output, 0);
    analogWrite(left_LPWM_Output, 255 );
}
