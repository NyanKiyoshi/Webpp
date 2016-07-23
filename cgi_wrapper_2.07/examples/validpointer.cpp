// This will show persistant data using GetDump and HiddenDump!
// Also added bugfix check for 2.07 ReturnValidPointer fix
// Suitable for use with CGI Wrapper 2.07 or later

// Copyright 2004 David Cutting (dcutting [at] purplepixie.org)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "../cgi_interface.h"
#include "../cgi_interface.cpp"

void screen_header(void);
void screen_footer(void);

int main(void)
{
screen_header();
CGI_Interface *i=new CGI_Interface(true);	// create object and
						// set to print errors

i->ReturnValidPointer=true;

i->AutoLoad();	// automatically load GET or POST data
printf("<b>Data Already Loaded:</b><br>");
i->PrintDump(); // print all loaded data to stdout

// RVP Check -- dies if not valid or shows (null) if clever printf funkyness
printf("Value of variable FishMonkey is... %s<br><br>",i->Fetch("FishMonkey"));

// Get a 'clean' URL whatever the method

char url[512];
strcpy(url,getenv("REQUEST_URI"));
bool blank=0;
for (int a=0; a<strlen(url); a++)
 {
 if (url[a]=='?') blank=true;
 if (blank) url[a]=0;
 }


// Now we make a random string for the variable name of the next
// user input.

char inp[]="abcdefghijklmnopqrstuvwxyz0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
srand(time(0));
float l=strlen(inp)-1;
// j=1+(int) (10.0*rand()/(RAND_MAX+1.0));
char vname[11];
for (int a=0; a<10; a++)
 {
 int c=1+(int) (l*rand()/(RAND_MAX+1.0));
 vname[a]=inp[c];
 }
vname[10]=0;

printf("You can now add a variable or persist the data as-is.<p>");

// Example of the GetDump Method
printf("<a href=%s?",url);
i->GetDump();
printf(">Click here to persist the current data</a><p>");

// Now using HiddenDump Method for GET and POST Forms

// GET First
printf("<form action=%s method=GET>",url);
i->HiddenDump();
printf("The GET Method Form:<br>");
printf("Add Variable %s <input type=text name=%s size=20><br>",vname,vname);
printf("<input type=submit value=\"Submit GET Form\"></form><p>");

// Now Post
printf("<form action=%s method=POST>",url);
i->HiddenDump();
printf("The POST Method Form:<br>");
printf("Add Variable %s <input type=text name=%s size=20><br>",vname,vname);
printf("<input type=submit value=\"Submit POST Form\"></form><p>");


delete i; // clean up list
screen_footer();
return 1;
}

void screen_header(void)
{
printf("Content-Type: text/html\n\n");
printf("<html><head><title>Persistant Data Example</title></head><body>\n\n");
printf("<a href=http://www.purplepixie.org/cgi/wrapper.php>");
printf("<img src=http://www.purplepixie.org/images/pixie_sml.jpg border=0> purplepixie.org CGI</a><p>\n\n");
}

void screen_footer(void)
{
printf("<p></body></html>");
}
