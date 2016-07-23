// Example implementing the GetDump() functionality from
// Version 2.02 onward.

#include <stdio.h>
#include <stdlib.h>

#include "../../cgi_interface.h"
#include "../../cgi_interface.cpp"

void pre(const char *name)
{
printf("%s: %s <br>\n",name,getenv(name));
}

void screen_header(void);
void screen_footer(void);

int main(void)
{
char url[512];
strcpy(url,getenv("REQUEST_URI"));
bool blank=0;
for (int a=0; a<strlen(url); a++)
 {
 if (url[a]=='?') blank=true;
 if (blank) url[a]=0;
 }

screen_header();
CGI_Interface *i=new CGI_Interface(true);
i->AutoLoad();
char *mode=i->Fetch("Mode");
if (mode!=0)
 {
 switch (mode[0])
  {
  case 'n':
   printf("<form action=%s method=post>\n",url);
   printf("<input type=hidden name=Mode value=a>\n");
   printf("Your Name Please <input type=text name=Name size=20><br>\n");
   printf("And your Age <input type=text name=Age size=4>\n");
   printf("<p>\n<input type=submit value=Proceed></form>");
   break;
  case 'a':
   printf("Ok %s, so you are %s years old!\n<p>",i->Fetch("Name"),i->Fetch("Age"));
   printf("<a href=%s?",url);
   i->GetDump();
   printf(">Click here to persist the data with DumpGet()</a><p>");
   printf("<a href=%s?Mode=n>Click to Start Again</a>",url);
   break;
  default:
   printf("<a href=%s?Mode=n>Click to Start</a>",url);
  }
 }
printf("<a href=%s?Mode=n>Click to Start</a>",url);
delete i;
screen_footer();
return 1;
}

void screen_header(void)
{
printf("Content-Type: text/html\n\n");
printf("<html><head><title>Example CGI Application</title></head><body>\n\n");
printf("<img src=http://www.purplepixie.org/images/pixie_sml.jpg> purplepixie.org CGI<p>\n\n");
}

void screen_footer(void)
{
printf("<p></body></html>");
}
