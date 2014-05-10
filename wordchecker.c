#include<stdio.h>
#include<string.h>
#include <stdlib.h>
#include <stdbool.h> 
#include <ctype.h>
#include <math.h>

#define MAXS 1000
#define MAXS2 5000
#define DICS 100

void convert_to_words(char *num);
bool is_valid_int(const char *str);
double is_similar(const char *str1, const char *str2);
void remove_punct_and_make_lower_case(char *p);
void remove_newline_ch(char *line);


int main()
{
   FILE *fp, *fpd, *fpo;
   char c;
   char buffer[MAXS];
   char outbuffer[MAXS2] = "";
   char dictionary[DICS];
   char* token;
	double flag;
	int isreplaced=0;
	int numcount=1;

   /* Open file for both reading and writing */
   fprintf(stderr, "Opening files ...\n");
   fp = fopen("input.txt", "r+");
   fpd = fopen("dictionary.txt", "r+");
   fpo = fopen("output.txt", "w+");

   /* Write data to the file */
   //fwrite(c, strlen(c) + 1, 1, fp);

   /* Seek to the beginning of the file */
   //fseek(fp, SEEK_SET, 0);

   /* Read and display data */
   //fread(buffer, sizeof(buffer)+1, 1, fp);
   fgets(buffer, sizeof(buffer), fp);
   remove_newline_ch(buffer);
   printf("Input paragraph;\n%s\n", buffer);
   
  /* while(!feof(fpd))
   {
   fgets(dictionary, sizeof(dictionary), fpd);	
   	printf("%s\n", dictionary);
   }*/
   
 token = strtok(buffer, " ");
while (token) {
		remove_punct_and_make_lower_case(token);
   // printf("\n\ntoken: %s, lenght: %d\n\n\n", token, strlen(token));

    // checking for numbers
    if(is_valid_int(token)){
    	printf("\nNumber %d: %s",numcount, token);
    	numcount++;
    	convert_to_words(token);
		strcat(outbuffer, token);
        strcat(outbuffer, " ");	
    } else {

	if(strlen(token) >= 4){


    // checking for spelling
    fseek(fpd, SEEK_SET, 0);
    	isreplaced = 0;
       while(!feof(fpd))
   {

   	flag = 0.0;
   fgets(dictionary, sizeof(dictionary), fpd);	
   remove_punct_and_make_lower_case(dictionary);
   remove_newline_ch(dictionary);
  // 	printf("%s\n", dictionary);
   	
   	   		   	if(strlen(token) >= 4){
   	flag = is_similar(token, dictionary);

   	/*{
   		strcat(outbuffer, token);
        strcat(outbuffer, " ");	
   	}if(flag == 0.0){
   	strcat(outbuffer, token);
        strcat(outbuffer, " ");		
   	} else */

	if(isreplaced != 1){
   	if(flag > 0.6){
   		strcat(outbuffer, dictionary);
        strcat(outbuffer, " ");	
        isreplaced = 1;
   	} else if(flag == 1.0){	
   	strcat(outbuffer, token);
        strcat(outbuffer, " ");	
		isreplaced = 1;	
   	}
	}
	   	} 
   }
   	if(isreplaced == 0){
	strcat(outbuffer, token);
        strcat(outbuffer, " ");		
	   	}
    } else {
		strcat(outbuffer, token);
        strcat(outbuffer, " ");	
	}
	} 
    token = strtok(NULL, " ");
}
   
   fwrite(outbuffer, strlen(outbuffer) + 1, 1, fpo);
   
   fclose(fp);
   fclose(fpd);
   fclose(fpo);
   
   return(0);
}


/* A function that prints given number in words */
void convert_to_words(char *num)
{
    int len = strlen(num);  // Get number of digits in given number
        /* The first string is not used, it is to make array indexing simple */
    char *single_digits[] = { "zero", "one", "two", "three", "four",
                              "five", "six", "seven", "eight", "nine"};
 
    /* The first string is not used, it is to make array indexing simple */
    char *two_digits[] = {"", "ten", "eleven", "twelve", "thirteen", "fourteen",
                     "fifteen", "sixteen", "seventeen", "eighteen", "nineteen"};
 
    /* The first two string are not used, they are to make array indexing simple*/
    char *tens_multiple[] = {"", "", "twenty", "thirty", "forty", "fifty",
                             "sixty", "seventy", "eighty", "ninety"};
 
     char *tens_power[] = {"hundred", "thousand", "ten thousand", "hundred thousand", "million"};
 
    /* Base cases */
    if (len == 0) {
        fprintf(stderr, "empty string\n");
        return;
    }
    if (len > 9) {
        fprintf(stderr, "Length more than 9 is not supported\n");
        return;
    }
 

 
    /* Used for debugging purpose only */
    printf("\n");
 
    /* For single digit number */
    if (len == 1) {
        printf("%s\n", single_digits[*num - '0']);
        return;
    }
 
     /* Iterate while num is not '\0' */
     while (*num != '\0') {
 
        /* Code path for first 2 digits */
        if (len >= 3) {
            if (*num -'0' != 0) {
                printf("%s ", single_digits[*num - '0']);
                printf("%s ", tens_power[len-3]); // here len can be 3 or 4
            }
            --len;
        }
 
        /* Code path for last 2 digits */
        else {
            /* Need to explicitly handle 10-19. Sum of the two digits is
               used as index of "two_digits" array of strings */
            if (*num == '1') {
                int sum = *num - '0' + *(num + 1)- '0';
                printf("%s\n", two_digits[sum]);
                return;
            }
 
            /* Need to explicitely handle 20 */
            else if (*num == '2' && *(num + 1) == '0') {
                printf("twenty\n");
                return;
            }
 
            /* Rest of the two digit numbers i.e., 21 to 99 */
            else {
                int i = *num - '0';
                printf("%s ", i? tens_multiple[i]: "");
                ++num;
                if (*num != '0')
                    printf("%s ", single_digits[*num - '0']);
            }
        }
        ++num;
    }
    printf("\n");
}

/* A function that check if the word is a number */
bool is_valid_int(const char *str)
{
   // Handle negative numbers.
   //
   if (*str == '-')
      ++str;

   // Handle empty string or just "-".
   //
   if (!*str)
      return false;

   // Check for non-digit chars in the rest of the stirng.
   //
   while (*str)
   {
      if (!isdigit(*str))
         return false;
      else
         ++str;
   }

   return true;
}

/* A function that check the percentage of similarity */
double is_similar(const char *str1, const char *str2) {
   
   double match;
   double count = 0;
   int len1, len2, i;
   
   len1 = strlen(str1);
   len2 = strlen(str2);
   
   if(len1 == len2){
   count = 0;
   		
   		for( i = 0 ; i < len1 ; i++) {
   			if(str1[i] == str2[i]){
   		//	printf("letter match\n");
			   count++;	
   			}
   		}
   } else { 
   count = 0;
   	//	printf("differrent sizes\n");
   		if(len1 < len2){
   			for( i = 0 ; i < len1 ; i++) {
   			if(str1[i] == str2[i]){
   		//	printf("letter match\n");
			   count++;	
   			}
   			}
   			
   		} else {
		count = 0;
   			for( i = 0 ; i < len2 ; i++) {
   			if(str1[i] == str2[i]){
   		//	printf("letter match\n");
			   count++;	
   			}
   			}
   		}
   		
   			
   		}
//   	printf("%d\n", count);
   	//	printf("%d\n", len1);
   		match = count/len1;
   	//		printf("match: %f\n", match);
   
   
   return match;
}

/* A function that removes punctuation */
void remove_punct_and_make_lower_case(char *p)
{
    char *src = p, *dst = p;

    while (*src)
    {
       if (ispunct((unsigned char)*src))
       {
          /* Skip this character */
          src++;
       }
       else if (isupper((unsigned char)*src))
       {
          /* Make it lowercase */
          *dst++ = tolower((unsigned char)*src);
          src++;
       }
       else if (src == dst)
       {
          /* Increment both pointers without copying */
          src++;
          dst++;
       }
       else
       {
          /* Copy character */
          *dst++ = *src++;
       }
    }

    *dst = 0;
}

/* A function that removes new lines */
void remove_newline_ch(char *line)
{
    int new_line = strlen(line) -1;
    if (line[new_line] == '\n')
        line[new_line] = '\0';
}
