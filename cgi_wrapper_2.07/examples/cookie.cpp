// CGI_Interface Cookie Demonstration

#include <stdio.h>
#include <stdlib.h>

#include "../cgi_interface.h"
#include "../cgi_interface.cpp"

void pre(const char *name)
{
printf("%s: %s <br>\n",name,getenv(name));
}

void screen_header(void);
void screen_footer(void);

int main(void)
{
CGI_Interface *i=new CGI_Interface(true);
i->AutoLoad();
i->CookieLoad();

char *name=i->Fetch("CookieSetName");
char *value=i->Fetch("CookieSetValue");

bool DidACookie=false;

if (name!=0)
 {
 if (value!=0)
  SetCookie(name,value);
 else
  SetCookie(name);
 DidACookie=true; 
 }
 
screen_header();
i->PrintDump();
if (DidACookie) printf("<br>Cookie Was Set: %s=%s<br><br>",name,value);
delete i;

// Note: No "normal" persist

printf("<br><br><form action=cookie method=post>");
printf("Create Cookie of Name <input type=text name=CookieSetName size=20> = ");
printf("<input type=text name=CookieSetValue size=20><br>");
printf("<input type=submit value=\"Create Cookie\">");
printf("</form><br><br>");
printf("<a href=cookie>Reload This Page i.e. see the cookies without adding another</a><br><br>");

screen_footer();
return 1;
}

void screen_header(void)
{
printf("Content-Type: text/html\n\n");
printf("<html><head><title>Example CGI Wrapper Cookie Functions</title></head><body>\n\n");
printf("<img src=http://www.purplepixie.org/images/pixie_sml.jpg> purplepixie.org CGI<p>\n\n");
}

void screen_footer(void)
{
printf("<p></body></html>");
}
