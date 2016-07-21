#!/bin/bash

APP_NAME="cgi_app.cgi"

# requires "fcgi" and "spawn-fcgi" packages installed
 ./compile.sh -- "$APP_NAME" && spawn-fcgi -p 8000 -n $APP_NAME
