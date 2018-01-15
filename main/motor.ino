void backward(){
  right_forward ();
  left_forward ();
}

void forward(){
  left_backward ();
  right_backward ();
}

void turn_left(){
  right_forward ();
  left_backward ();
  
}

void turn_right(){
  right_backward ();
  left_forward ();
  
}



void Stop(){
    analogWrite(right_LPWM_Output, 0);
    analogWrite(right_RPWM_Output, 0);
    analogWrite(left_LPWM_Output, 0);
    analogWrite(left_RPWM_Output, 0);
}


void right_forward (){
    analogWrite(right_LPWM_Output, 0);
    analogWrite(right_RPWM_Output, sspeed );
}

void left_forward (){
    analogWrite(left_LPWM_Output, 0);
    analogWrite(left_RPWM_Output, sspeed );
}


void right_backward (){
    analogWrite(right_LPWM_Output, sspeed );
    analogWrite(right_RPWM_Output, 0);
}

void left_backward (){
    analogWrite(left_RPWM_Output, 0);
    analogWrite(left_LPWM_Output, sspeed );
}
