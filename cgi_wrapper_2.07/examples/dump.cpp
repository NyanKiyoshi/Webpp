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
i->PrintDump();
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
