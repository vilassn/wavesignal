#!/bin/bash
# WaveSignal JavaFX Application Launcher
# Run from /home/vilas/wavesignal directory

echo "🚀 Starting WaveSignal JavaFX Application..."
echo "📁 Running from: /home/vilas/wavesignal"
echo "📦 JAR file: wavesignal.jar"

# Check if JAR file exists
if [ ! -f "libs/wave.jar" ]; then
    echo "❌ Error: wavesignal.jar not found in current directory"
    echo "📂 Current directory: $(pwd)"
    echo "📋 Files in current directory:"
    ls -la
    exit 1
fi

# Check if runtime exists
RUNTIME_DIR="/home/vilas/wavesignal/runtime"
if [ ! -d "$RUNTIME_DIR" ]; then
    echo "❌ Error: Runtime directory not found at $RUNTIME_DIR"
    echo "Please ensure the runtime is installed at $RUNTIME_DIR"
    exit 1
fi

# Set Java and JavaFX paths
JAVA_HOME="$RUNTIME_DIR/jdk-21.0.1"
JAVAFX_HOME="$RUNTIME_DIR/javafx-sdk-21.0.1"

# Check if Java exists
if [ ! -d "$JAVA_HOME" ]; then
    echo "❌ Error: Java not found at $JAVA_HOME"
    exit 1
fi

# Check if JavaFX exists
if [ ! -d "$JAVAFX_HOME" ]; then
    echo "❌ Error: JavaFX not found at $JAVAFX_HOME"
    exit 1
fi

echo "✅ Runtime found at: $RUNTIME_DIR"
echo "☕ Java: $JAVA_HOME"
echo "🎨 JavaFX: $JAVAFX_HOME"
echo ""

# Run the application
echo "🌐 Starting application..."
echo "📊 Press Ctrl+C to stop the application"
echo ""

$JAVA_HOME/bin/java \
    --module-path "$JAVAFX_HOME/lib" \
    --add-modules javafx.controls,javafx.fxml,javafx.web \
    -jar libs/wave.jar
