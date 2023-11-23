#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void declaration()
{
    int width = 80;
    char *string = "Declaration";

    int strLen = strlen(string);

    if (strLen < width) {
        int padding = (width - strLen) / 2;
        printf("%*s%s%*s\n", padding, " ", string, padding, " ");
    } else {
        printf("%s\n", string);
    }

    printf("SITs policy on copying does not allow the students to copy source code as well as assessment solutions from another person or other places. It is the students responsibility to guarantee that their assessment solutions are their own work. Meanwhile, the students must also ensure that their work is not accessible by others. Where such plagiarism is detected, both of the assessments involved will receive ZERO mark.\n");
    printf("\nWe hereby declare that: \n");
    printf("- We fully understand and agree to the abovementioned plagiarism policy.\n");
    printf("- We did not copy any code from others or from other places.\n");
    printf("- We did not share our codes with others or upload to any other places for public access.\n");
    printf("- We agree that our project will receive Zero mark if there is any plagiarism detected.\n");
    printf("\nDeclared by: Group Name: P1_T5 \n");
    printf("Team members: \n");
    printf("1. Brandon Koh Lin Xi\n2. Joel Chan Wen Jun\n3. Muhammad Hazley Bin Samsudin\n4. Lucas Koh Shoo\n5. Christopher Yong Wei Jie\n");
    printf("Date: 23 November 2023. \n"); 
  
}
