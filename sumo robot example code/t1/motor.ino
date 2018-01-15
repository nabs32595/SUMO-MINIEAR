void Stop(){

    digitalWrite(right_LPWM_Output, 0);
    digitalWrite(right_RPWM_Output, 0);
   }

void right_forward (int speedd){
    digitalWrite(right_LPWM_Output, 0);
    digitalWrite(right_RPWM_Output, speedd);
}

void left_forward (int speedd){
    digitalWrite(left_RPWM_Output, speedd);
    digitalWrite(left_LPWM_Output, 0);
}


void right_backward (int speedd){
    digitalWrite(right_LPWM_Output, speedd);
    digitalWrite(right_RPWM_Output, 0);
}

void left_backward (int speedd){
    digitalWrite(left_RPWM_Output, 0);
    digitalWrite(left_LPWM_Output, speedd );
}


