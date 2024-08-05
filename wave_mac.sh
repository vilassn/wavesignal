#!/bin/bash
# Script to run wave on Mac OS
runtime/jdk-21.0.1.jdk/Contents/Home/bin/java --module-path runtime/javafx-sdk-21.0.1/lib --add-modules javafx.controls,javafx.fxml,javafx.web -jar libs/wave.jar > /dev/null 2>&1 &