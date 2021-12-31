// return the larger number in a and b
int max(int a, int b) {
  if (a > b)
    return a;
  return b;
}

//return 1 if x is between left and right
int between(int x, int left, int right) {
  if (x >= left && x < right)
    return 1;
  //return 0 otherwise
  return 0;
}

//return 1 if y is equal to either num1 or num2
int equal(int y, int num1, int num2) {
  if (y == num1 || y == num2)
    return 1;
  //return 0 otherwise
  return 0;
}

//combine between and equal with the logic and
int comb(int a, int a_off, int b, int b_off, int size) {
  int ifbetween = between(a, a_off, a_off + size);
  int ifequal = equal(b, b_off, b_off + size -1);
  // return with logic and
  return ifbetween * ifequal;
}



void squares(int size1, int x_offset, int y_offset, int size2) {
  //compute the max of size1 and (x_offset + size2).  Call this w
  int w = max(size1, x_offset + size2);
  //compute the max of size1 and (y_offset + size2).  Call this h
  int h = max(size1, y_offset + size2);
  //count from 0 to h. Call the number you count with y
  for (int y = 0; y < h; y++) {
    //count from 0 to w. Call the number you count with x
    for (int x = 0; x < w; x++) {

      //Declare two conditions as int
      int condition1, condition2;

      //set condition1 to be
      //    ((x is between x_offset  and x_offset +size2) AND 
      //     y is equal to either y_offset OR y_offset + size2 - 1 )
      condition1 = comb(x, x_offset, y, y_offset, size2);

      //set condition2 to be
      //    ((y is between y_offset and y_offset + size2) AND
      //     x is equal to either x_offset OR x_offset + size2 -1)
      condition2 = comb(y, y_offset, x, x_offset, size2);

      //check if  EITHER condition1 OR condition2
      if (condition1 || condition2)
        // if so, print a *
	printf("*");

      //if not,
      // check if EITHER
      //    x is less than size1 AND (y is either 0 or size1-1)
      // OR
      //    y is less than size1 AND (x is either 0 or size1-1)
      else if (comb(x, 0, y, 0, size1) || comb(y, 0, x, 0, size1))
	//if so, print a #
	printf("#");

      //else print a space
      else
	printf(" ");

    //when you finish counting x from 0 to w,
    }

    //print a newline
    printf("\n");

  //finish counting y
  }

}
