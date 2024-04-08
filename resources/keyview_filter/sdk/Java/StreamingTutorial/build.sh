#!/bin/sh

# Set the location of JAVA_HOME and ANT_HOME for your environment.
JAVA_HOME=/opt/homebrew/opt/openjdk@11
ANT_HOME=/opt/homebrew/bin
export JAVA_HOME
export ANT_HOME

PATH=$JAVA_HOME/bin:$ANT_HOME:$PATH
export PATH

ant jar