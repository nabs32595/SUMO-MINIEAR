
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
}

void turn_right(){
  right_turn_forward ();
  right_turn_backward ();
}



void Stop(){
    analogWrite(right_LPWM_Output, 0);
    analogWrite(right_RPWM_Output, 0);
    analogWrite(left_RPWM_Output, 0);
    analogWrite(left_LPWM_Output, 0);
}


void right_forward (){
    analogWrite(right_LPWM_Output, 0);
    analogWrite(right_RPWM_Output, speedy);
}

void left_forward (){
    analogWrite(left_RPWM_Output, 0);
    analogWrite(left_LPWM_Output, speedy);
}


void right_backward (){
    analogWrite(right_LPWM_Output, speedy);
    analogWrite(right_RPWM_Output,0);
}

void left_backward (){
    analogWrite(left_RPWM_Output, speedy);
    analogWrite(left_LPWM_Output, 0);
}
void right_turn_forward (){
    analogWrite(right_LPWM_Output, 85);
    analogWrite(right_RPWM_Output, 0);
}
void right_turn_backward (){
    analogWrite(left_RPWM_Output, 0);
    analogWrite(left_LPWM_Output, 85);
}


