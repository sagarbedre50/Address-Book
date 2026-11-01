#include "contact.h"
#include<string.h>
#include<stdio.h>
#include<ctype.h> 
#include<stdlib.h>
void initialize(AddressBook *addressBook)
{
    addressBook->contactCount=0;
    int i=0;
    FILE *fp;
    fp=fopen("contacts.txt","r");
    while (fscanf(fp," %49[^,],%19[^,],%49[^\n]",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email)==3)
    {
        addressBook->contactCount++;
        i++;
    }
    fclose(fp);
    return;
}
void listContacts(AddressBook *addressBook)    // List Contact -------------------------------------------------------------------------------//
{
    int i=0;
    printf("+------------------------------------------------------------------------+\n");
    printf("%s %-6s %s %-20s %s %-15s %s %-20s %s\n","|","Sr.No","|","Name","|","Phone","|","E-mail","|");
    printf("+------------------------------------------------------------------------+\n");
   for ( i = 0; i < addressBook->contactCount; i++)
   {
    printf("%s %-6d %s %-20s %s %-15s %s %-20s %s\n","|",i+1,"|",addressBook->contacts[i].name,"|",addressBook->contacts[i].phone,"|",addressBook->contacts[i].email,"|");
   }
   printf("\n+------------------------------------------------------------------------+\n");
   return;
}
int check_name(char name_s[])  // Check Name Validations
{
    int i=0;
    if(strlen(name_s)<3)
    return 1;
    for(i=0;i<strlen(name_s);i++)
    {
       int result=isalpha(name_s[i]);
       if(result==0 && name_s[i]!=' ')
       return 2;
       if(name_s[i]==' ' && name_s[i+1]==' ' && name_s[i]!=strlen(name_s)-1)
       return 5;
    }
    return 0;
}
int check_phone(char phone_s[])  // Check mobile validations
{
   int i=0;
   int ok;
   if(strlen(phone_s)!=10)
    return 1;
  if(phone_s[0]<'6' || phone_s[0]>'9')
  return 2;
    for ( i = 0; i < 10; i++)
    {
        int result=isdigit(phone_s[i]);
        if(result==0)
        return 3; 
    }
    return 0;
}
int check_email(char email_s[])  //Check Mail Validations
{
    int i,count=0,found=0;
    if(email_s[0]=='@')
    return 7;
    for ( i = 0; i < strlen(email_s); i++)
    {
        if(email_s[i]=='@')
            count++;
        if(email_s[i]=='.')
            found++;
    }
    if(count==0)  return 1;
    if(count>1)  return 2;
    if(found==0)  return 3;
    if(found>1)   return 4;
    for ( i = 0; i < strlen(email_s); i++)
    {
        if(islower(email_s[i]) || isdigit(email_s[i])){}

        else if(email_s[i]=='@' || email_s[i]=='.'){}

        else if(isupper(email_s[i])) return 5;
    
        else return 6;

        if(email_s[i]=='.')
        {
            if(i==strlen(email_s)-4){}
            else{
                if(i<strlen(email_s)-4)
                return 11;
                else return 12;   
            }
            if(email_s[i+1]=='c' && email_s[i+2]=='o' && email_s[i+3]=='m'){}
            else
                return 12; 
        }
    }
    return 0;    
}
void createContact(AddressBook *addressBook)  // Creat Contact --------------------------------------------------------------------------//
{
    int i=addressBook->contactCount,result=0,count=0,final=0,attempt=0;
     char name_s[100],phone_s[100],email_s[100];
    while(1)
    {
        printf("\nEnter the name: ");
        scanf(" %49[^\n]",name_s);
        int ffound=0;
        if(strlen(name_s)>0)
        {
           for(int j=0 ; j < addressBook->contactCount; j++)
           {
               ffound =0;
              int result=strcmp(addressBook->contacts[j].name,name_s);
              if(result==0){
                ffound++;
                printf("\n\033[31m Name must be Unique !\033[0m\n");
                break;
                }  
           }
        }
        attempt++;
        if(ffound<1)
        {
            result=check_name(name_s);
        
        if(result==1)
        printf("\n\033[31mName must contain atleast 4 characters\033[0m\n");

        else if(result==2)
        printf("\n\033[31mName should contain only alphabate\033[0m\n");

        else if(result==5)
        printf("\n\033[31mIn two words only one Space are allowed\033[0m\n");

        else if(result==0)
        {
            final++;
            break;  
        }
     }
     if(attempt==3)
        {
            printf("\033[31mYou completed your 3 attempts please try again !\033[0m\n");
            return;
        }
    }
    attempt=0;
    while(1)
    {
        int serch=0;
        printf("\nEnte the mobile No: ");
        scanf(" %[^\n]",phone_s);
        if(strlen(phone_s)>0)
        {
            for (int k  = 0; k < addressBook->contactCount; k++)
          {
            serch=0;
            int result=strcmp(addressBook->contacts[k].phone,phone_s);
            if(result==0){
                printf("\n\033[31mMobile number must be unique !\033[0m\n");
                serch++;
                break;
            }
          } 
        } 
        attempt++;
       if(serch==0) 
       {
            int result=check_phone(phone_s);
            if(result==2)
            printf("\n\033[31mFirst number must contain range for 6 to 9\033[0m\n");

            else if(result==4)
            printf("\n\033[31mAlphabates are not allowd in the number \033[0m\n");

            else if(result==3)
            printf("\n\033[31mOther than Digits not allowed\033[0m\n");
        
            else if(result==1)
            printf("\n\033[31mNumber must contain 10 digits\033[0m\n");
        
            else if(result==0)
            {
              final++;
              break;
            }
        }
        if(attempt==3)
        {
            printf("\033[31mYou completed your 3 attempts please try again !\033[0m\n");
            return;
        }
    }
    attempt=0;
    while (1)
    {
        int ffound=0;
        printf("\nEnter the email: ");
        scanf(" %49[^\n]",email_s);
        if(strlen(email_s)>0)
        {
           for(int j=0 ; j < addressBook->contactCount; j++)
           {
               ffound =0;
              int result=strcmp(addressBook->contacts[j].email,email_s);
              if(result==0){
                ffound++;
                printf("\n\033[31mEmail id must be Unique !\n");
                break;
                }  
           }
        }
        attempt++;
        if(ffound==0)
        {
            int result=check_email(email_s);
            if(result==1)
            printf("\n\033[31mMissing @ character\033[0m\n");

            else if(result==2)
            printf("\n\033[31mEmail must contain only one @ character\033[0m\n");

            else if (result==3)
            printf("\n\033[31mMissing . character\033[0m\n");
        
            else if(result==4)
            printf("\n\033[31mEmail must contain only one . character\033[0m\n");

            else if(result==5)
            printf("\n\033[31mEmail must contain only lower Alphabates\033[0m\n");

            else if(result==6)
            printf("\n\033[31mInvalid symbol\033[0m\n");

            else if(result==7)
            printf("\n\033[31mFirst character @ not allowed \033[0m\n");

            else if(result==11)
            printf("\n\033[31mExtra character after the Domain Not allowed\033[0m\n");

            else if(result==12)
            printf("\n\033[31mInvalid Domain\033[0m\n");

           else if(result==0)
           {
             final++;
             break;
            }
        }
        if(attempt==3)
        {
            printf("\033[31mYou completed your 3 attempts please try again !\033[0m\n");
            return;
        }
    }
            if(final==3) 
             {
                strcpy(addressBook->contacts[i].name,name_s);
                strcpy(addressBook->contacts[i].phone,phone_s);
                strcpy(addressBook->contacts[i].email,email_s);
                addressBook->contactCount++;
                printf("   +-------------------------------+\n");
                printf("   |  \033[32m Contact Saved Successfully  \033[0m|\n");
                printf("   +-------------------------------+\n");
             }
            return ;
}
void saveContactsToFile(AddressBook *AddressBook) // Save Contact ------------------------------------------------------------------------//
{
    FILE *fp;
    int i;
    fp=fopen("contacts.txt","w");
    for ( i = 0; i < AddressBook->contactCount; i++){
        fprintf(fp,"%s,%s,%s\n",AddressBook->contacts[i].name,AddressBook->contacts[i].phone,AddressBook->contacts[i].email);
    }
    fclose(fp);
    return;  
}
void searchContact(AddressBook *addressBook)  // Serch Contact -----------------------------------------------------------------------------//
{
    int i,option=0,index=0,attempt=0;
    while (1)
    {
        char key_word[100];
        int found=0,count=0,arr[100];
        printf("\n+---------------------------+\n");
        printf("| \033[32m Serch by any keyword  \033[0m   |\n");
        printf("+---------------------------+\n");

        printf("Enter key word :");
        scanf(" %[^\n]",key_word);
        
        for(int i=0;i<addressBook->contactCount;i++)
        {
            char *result=strcasestr(addressBook->contacts[i].name,key_word);
            char *result1=strcasestr(addressBook->contacts[i].phone,key_word);
            char *result2=strcasestr(addressBook->contacts[i].email,key_word);
            if(result!=NULL || result1!=NULL || result2!=NULL)
            {
                if(found==0)
                {
                    printf("+------------------------------------------------------------------------+\n");
                    printf("%s %-6s %s %-20s %s %-15s %s %-20s %s\n","|","Sr.No","|","Name","|","Phone","|","E-mail","|");
                    printf("+------------------------------------------------------------------------+\n");
                    found++;
                }
                printf("%s %-6d %s %-20s %s %-15s %s %-20s %s\n","|",count+1,"|",addressBook->contacts[i].name,"|",addressBook->contacts[i].phone,"|",addressBook->contacts[i].email,"|");
                arr[count]=i;
                count++;
            }
        }
        attempt++;
        if(count>0)
        printf("+------------------------------------------------------------------------+\n");
        if(count>0 && count!=1)
        {
           int option=0;
           printf("Enter the Sr.No : ");
           scanf("%d",&option);
           index=arr[option-1];
           if(option>=0 && option<=count )
            {
                printf("+------------------------------------------------------------------------+\n");
                printf("%s %-6d %s %-20s %s %-15s %s %-20s %s\n","|",1,"|",addressBook->contacts[index].name,"|",addressBook->contacts[index].phone,"|",addressBook->contacts[index].email,"|");
                printf("+------------------------------------------------------------------------+\n");
                break;
            }
          else{
              printf("\n\033[31m Invalit Option Try again !\033[0m\n");
              }
        }
        else if(count==0)
        printf("\n\033[31mContact not found try again Try again !\033[0m\n");
        if(attempt==3)
        {
            printf("\033[31mYou completed your 3 attempts please try again !\033[0m\n");
            return;
        }
    }
    return;
}
void editContact(AddressBook *addressBook)  // Edit Contact ----------------------------------------------------------------------------------------//
{
    int i,option=0,index=0,count=0,attempt=0;
    while (1)
    {
        char key_word[100];
        int found=0,count=0,arr[100];  
       printf("\n+---------------------------+\n");
        printf("| \033[32m Serch by any keyword  \033[0m   |\n");
        printf("+---------------------------+\n");

        printf("Enter key word :");
        scanf(" %[^\n]",key_word);
        
        for(int i=0;i<addressBook->contactCount;i++)
        {
            char *result=strcasestr(addressBook->contacts[i].name,key_word);
            char *result1=strcasestr(addressBook->contacts[i].phone,key_word);
            char *result2=strcasestr(addressBook->contacts[i].email,key_word);
            if(result!=0 || result1!=0 || result2!=0)
            {
                if(found==0)
                {
                    printf("+------------------------------------------------------------------------+\n");
                    printf("%s %-6s %s %-20s %s %-15s %s %-20s %s\n","|","Sr.No","|","Name","|","Phone","|","E-mail","|");
                    printf("+------------------------------------------------------------------------+\n");
                    found++;
                }
                printf("%s %-6d %s %-20s %s %-15s %s %-20s %s\n","|",count+1,"|",addressBook->contacts[i].name,"|",addressBook->contacts[i].phone,"|",addressBook->contacts[i].email,"|");
                arr[count]=i;
                count++;
            }
        }
        if(count>0)
        printf("+------------------------------------------------------------------------+\n");
        attempt++;

        if(count>0)
        {
             int option=0;
             printf("Enter the Sr.No : ");
             scanf("%d",&option);

             if(option>0 && option<=count)
             {
               index=arr[option-1];
               break;
             }
            else{
                printf("\n\033[31m Invalit Option Try again !\033[0m");
                }
        }
        else
        printf("\n\033[31m Contact not found try again !\033[0m");

        if(attempt==3)
        {
            printf("\n\033[31mYou completed your 3 attempts please try again !\033[0m\n");
            return;
        }
    }
    
    attempt=0;
    while (1)
    {
        int option=0,i=index;
        char name_e[100], phone_e[100],email_e[100];
       printf("\n+------------------+\n");
       printf("| 1.Edit name      |\n");
       printf("| 2.Edit phone     |\n");
       printf("| 3.Edit E-mail    |\n");
       printf("| 4.Stop           |\n");
       printf("+------------------+\n");
       printf("Enter the option ");
       scanf("%d",&option);
    if(option==1)
    {
       while(1)
       {
         printf("Enter the new name: ");
         scanf(" %[^\n]",name_e);
         int ffound=0;
         if(strlen(name_e)>0)
         {
            for(int j=0 ; j < addressBook->contactCount; j++)
            {
               ffound =0;
              int result=strcmp(addressBook->contacts[j].name,name_e);
              if(result==0){
                ffound++;
                printf("\n\033[31mName must be Unique !\033[0m\n");
                break;
                }  
           }
        }
        attempt++;
        if(ffound<1)
        {
            int result=check_name(name_e);
        
           if(result==1)
           printf("\n\033[31mName must contain atleast 4 characters\033[0m\n");

           else if(result==2)
           printf("\n\033[31mName should contain only alphabate\033[0m\n");

           else if(result==5)
           printf("\n\033[31mIn two words only one Space are allowed\033[0m\n");

           else if(result==0)
           {
              strcpy(addressBook->contacts[i].name,name_e);
              printf("\033[32mChange Saved Succesfully !\033[0m\n");
              break;  
           }
        }
        if(attempt==3)
        {
            printf("\n\033[31mYou completed your 3 attempts please try again !\033[0m\n");
            return;
        }
     }
    }
    attempt=0;
    if(option==2)
    {
        while (1)
        {
           int serch=0;
           printf("\nEnte the mobile No: ");
           scanf(" %[^\n]",phone_e);
           if(strlen(phone_e)>0)
           {
                for (int k  = 0; k < addressBook->contactCount; k++)
               {
                 serch=0;
                 int result=strcmp(addressBook->contacts[k].phone,phone_e);
                 if(result!=0){}

                 else{
                     printf("\n\033[31mMobile number must be unique !\033[0m\n");
                     serch++;
                     break;
                    }
                }
            }
            attempt++;
          if(serch==0)
           {
             int result=check_phone(phone_e);
             if(result==2)
             printf("\n\033[31mFirst number must contain range for 6 to 9\033[0m\n");

             else if(result==4)
             printf("\n\033[31mAlphabates are not allowd in the number \033[0m\n");

             else if(result==3)
             printf("\n\033[31mOther than Digits not allowed\033[0m\n");
        
             else if(result==1) 
             printf("\n\033[31mNumber must contain 10 digits\033[0m\n");
        
             else if(result==0)
             {
               strcpy(addressBook->contacts[i].phone,phone_e);
               printf("\033[32mChange Saved Succesfully !\033[0m\n");
               break;
             }
          }
          if(attempt==3)
          {
            printf("\n\033[31mYou completed your 3 attempts please try again !\033[0m\n");
            return;
          }
        }
    }
    attempt=0;
    if(option==3)
    {
           while (1)
           {
              int ffound=0;
              printf("\nEnter the email: ");
              scanf(" %49[^\n]",email_e);
            if(strlen(email_e)>0)
            {
                 for(int j=0 ; j < addressBook->contactCount; j++)
                {
                   ffound =0;
                    int result=strcmp(addressBook->contacts[j].email,email_e);
                    if(result!=0){}

                    else{
                           ffound++;
                           printf("\n\033[31mEmail id must be Unique !\033[0m\n");
                           break;
                        }
                }
            }
            attempt++;
           if(ffound==0)
           {
              int result=check_email(email_e);
       
               if(result==1)
               printf("\n\033[31mMissing @ character\033[0m\n");

               else if(result==2)
               printf("\n\033[31mEmail must contain only one @ character\033[0m\n");

               else if (result==3)
               printf("\n\033[31mMissing . character\033[0m\n");
        
               else if(result==4)
               printf("\n\033[31mEmail must contain only one . character\033[0m\n");

               else if(result==5)  
               printf("\n\033[31mEmail must contain only lower Alphabates\033[0m\n");

               else if(result==6)
               printf("\n\033[31mInvalid symbol\033[0m\n");

               else if(result==7)
               printf("\n\033[31mFirst character @ not allowed \033[0m\n");

               else if(result==11)
               printf("\n\033[31mExtra character after the Domain Not allowed\033[0m\n");

               else if(result==12)
               printf("\n\033[31m Invalid Domain !\033[0m\n");

               else if(result==0)
              {
                 strcpy(addressBook->contacts[i].email,email_e);
                 printf("\033[32mChange Saved Succesfully !\033[0m\n");
                break;
              }
              if(attempt==3)
             {
               printf("\n\033[31mYou completed your 3 attempts please try again !\033[0m\n");
               return;
             }
            }
        }
    } 
      if (option==4)
        break;
        
       if(option<1 || option>4)
        printf("\n\033[31m Invalit Option Try again !\033[0m");    
   }
}
void deleteContact(AddressBook *addressBook)     // Delet Contact-----------------------------------------------------------------------------//
{
    int i,index=0,count=0,option=0,attempt=0;;
    while (1)
    { 
        char key_word[100];
        int arr[100],found=0,count=0;
        printf("\n+---------------------------+\n");
        printf("| \033[32m Serch by any keyword  \033[0m   |\n");
        printf("+---------------------------+\n");
        printf("Enter key word :");
        scanf(" %[^\n]",key_word);
        attempt++;
        for(int i=0;i<addressBook->contactCount;i++)
        {
            char *result=strcasestr(addressBook->contacts[i].name,key_word);
            char *result1=strcasestr(addressBook->contacts[i].phone,key_word);
            char *result2=strcasestr(addressBook->contacts[i].email,key_word);
            if(result!=0 || result1!=0 || result2!=0)
            {
                if(count==0)
                {
                    printf("+------------------------------------------------------------------------+\n");
                    printf("%s %-6s %s %-20s %s %-15s %s %-20s %s\n","|","Sr.No","|","Name","|","Phone","|","E-mail","|");
                    printf("+------------------------------------------------------------------------+\n");
                    count++;
                }
                printf("%s %-6d %s %-20s %s %-15s %s %-20s %s\n","|",found+1,"|",addressBook->contacts[i].name,"|",addressBook->contacts[i].phone,"|",addressBook->contacts[i].email,"|");
                arr[found]=i;
                found++;
            }
        }
        if(attempt==3)
        {
            printf("\n\033[31mYou completed your 3 attempts please try again !\033[0m\n");
            return;
        }
        if(count>0)
        printf("+------------------------------------------------------------------------+\n");
        int num=0;
        if(count>0)
        {
            int option=0;
            printf("Enter the index : ");
            scanf("%d",&option);
            if(option>0 && option<=found)
            index=arr[option-1];
            else
             printf("\n\033[31m Invalit Option Try again !\033[0m");
        }
        else
        printf("\n\033[31mContact not found try again !\033[0m");
        if(index>=0)
        {
            printf("\n\033[31mYou confirmed to delet this contact !\033[0m\n");
            printf("1 = Yes || 2 = No\n");
            printf("Confirm here: ");
            scanf("%d",&num);
        }
       if(num==1)
       {
        for ( i = index; i < addressBook->contactCount-1; i++)
        {
           strcpy (addressBook->contacts[i].name,addressBook->contacts[i+1].name);
           strcpy (addressBook->contacts[i].phone,addressBook->contacts[i+1].phone);
           strcpy (addressBook->contacts[i].email,addressBook->contacts[i+1].email);
        }    
        addressBook->contactCount--;
        printf("   +-----------------------------+\n");
        printf("   |   \033[32m  Deleted Successfully  \033[0m  |\n");
        printf("   +-----------------------------+\n");
        break;
       }
   } return;
}