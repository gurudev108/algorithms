/* Given a string s, return true if the s can be palindrome after deleting at most one character from it. */

/* test case failed which had 20 chars and both s[i] == s[j-1] and s[i+1] and s[j] are equal -- TRY RECURSION
bool validPalindrome(char * s){
  int len = strlen(s);
  int i = 0;
  int j = len - 1;
  int fail = 0;
  while((i<j) && (fail<2)) {
     printf("\nLoop i=%d j=%d %c %c", i, j, s[i], s[j]);
     if (s[i] == s[j]){
        i++; j--;
        continue;
     } else {
       fail++;
       printf("\nfail=%d i=%d j=%d", fail, i, j);
       if ((j == (i+1)) && (fail <=1)) return true;
       if (fail>1) return false;
       if (s[i] == s[j-1]){
          j--;
       } else if (s[i+1] == s[j]){
          i++;
       } else {
          fail++;
          printf("\nelse block fail=%d i=%d j=%d", fail, i, j);
       }
     }
  }

  if (fail < 2) return true;
  return false;
}
*/


bool checkPalindrome(char* s, int i, int j){
   while (i<j){
      if (s[i] != s[j]){
        return false;
      } else {
         i++;
         j--;
      }
   }
   return true;
}

bool validPalindrome(char * s){
  int i =0;
  int j = strlen(s) - 1;
  while (i<j) {
     if (s[i] != s[j]){
        return (checkPalindrome(s,i+1, j) || checkPalindrome(s, i, j-1));
     }
     i++;
     j--;
  }
  return true;
}

