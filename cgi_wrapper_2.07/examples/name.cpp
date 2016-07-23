#include <stdio.h>
#include <stdlib.h>

#include "../src/cgi_interface.h"
#include "../src/cgi_interface.cpp"

void pre(const char *name)
{
printf("%s: %s <br>\n",name,getenv(name));
}

void screen_header(void);
void screen_footer(void);

int main(void)
{
screen_header();
CGI_Interface *i=new CGI_Interface(true);
i->AutoLoad();
char *mode=i->Fetch("Mode");
printf("<form action=%s method=post>\n",getenv("REQUEST_URI"));
if (mode!=0)
 {
 switch (mode[0])
  {
  case 'n':
   printf("<input type=hidden name=Mode value=a>\n");
   printf("Your Name Please <input type=text name=Name size=20>\n");
   break;
  case 'a':
   printf("<input type=hidden name=Mode value=b>\n");
   printf("<input type=hidden name=Name value=\"%s\">\n",i->Fetch("Name"));
   printf("Hello %s, how old are you? ",i->Fetch("Name"));
   printf("<input type=text name=Age size=4>\n");
   break;
  case 'b':
   printf("<input type=hidden name=Mode value=StartAgain>\n");
   printf("Ok %s, so you are %s years old!\n",i->Fetch("Name"),i->Fetch("Age"));
   break;
  default:
   printf("<input type=hidden name=Mode value=n>\n");
  }
 }
else printf("<input type=hidden name=Mode value=n>\n");
printf("<p>\n<input type=submit value=Proceed></form>");
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
