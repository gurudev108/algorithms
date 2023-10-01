bool isStrobogrammatic(char * num){
  int len = strlen(num);
  char inverted[50];
    strcpy(inverted, num);
    printf("Copied string %s", inverted);
    for(int i = 0; i < len; i++)
    {
        switch(inverted[i])
        {
            case '6':
                inverted[len-1-i] = '9';
                break;
            case '9':
                inverted[len-1-i] = '6';
                break;
            case '8':
                inverted[len-1-i] = '8';
                break;
            case '1':
                inverted[len-1-i] = '1';
                break;
            case '0':
                inverted[len-1-i] = '0';
                break;
            default:
                printf("%c defaulted", inverted[i]);
                return false;
        }
    }
    printf("Inverted string %s", inverted);
    if(strcmp(num, inverted)==0)
        return true;
    else
        return false;
}
