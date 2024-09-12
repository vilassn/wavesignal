#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <sys/stat.h>
#include <curl/curl.h>
#include <archive.h>
#include <archive_entry.h>

#ifdef _WIN32
#include <direct.h>
#include <windows.h>
#else
#include <unistd.h>
#endif

// Function to check if a directory exists
bool DirectoryExists(const std::string& dirName) {
    struct stat info;
    if (stat(dirName.c_str(), &info) != 0)
        return false;
    return (info.st_mode & S_IFDIR) != 0;
}

// Function to create a directory
bool CreateDirectory(const std::string& dirName) {
#ifdef _WIN32
    return _mkdir(dirName.c_str()) == 0 || errno == EEXIST;
#else
    return mkdir(dirName.c_str(), 0755) == 0 || errno == EEXIST;
#endif
}

// Function to write data received from CURL
size_t WriteData(void* ptr, size_t size, size_t nmemb, FILE* stream) {
    return fwrite(ptr, size, nmemb, stream);
}

// Function to download a file using CURL
bool DownloadFile(const std::string& url, const std::string& local_path) {
    CURL* curl = curl_easy_init();
    if (curl) {
        FILE* fp = fopen(local_path.c_str(), "wb");
        if (!fp) {
            curl_easy_cleanup(curl);
            return false;
        }

        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteData);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
        CURLcode res = curl_easy_perform(curl);
        fclose(fp);
        curl_easy_cleanup(curl);

        return res == CURLE_OK;
    }
    return false;
}

// Function to extract a TAR.GZ file
bool ExtractTarGz(const std::string& tar_path, const std::string& extract_path) {
    struct archive* a = archive_read_new();
    struct archive_entry* entry;
    archive_read_support_format_tar(a);
    archive_read_support_filter_gzip(a);
    int r = archive_read_open_filename(a, tar_path.c_str(), 10240);
    if (r != ARCHIVE_OK)
        return false;

    while (archive_read_next_header(a, &entry) == ARCHIVE_OK) {
        std::string full_path = extract_path + "/" + archive_entry_pathname(entry);
        archive_entry_set_pathname(entry, full_path.c_str());
        archive_read_extract(a, entry, ARCHIVE_EXTRACT_TIME);
    }
    archive_read_close(a);
    archive_read_free(a);
    return true;
}

// Function to download and extract files
void DownloadAndExtract(const std::vector<std::string>& urls, const std::string& runtime_dir) {
    for (size_t i = 0; i < urls.size(); ++i) {
        const std::string& url = urls[i];
        std::string local_file = runtime_dir + "/" + url.substr(url.find_last_of('/') + 1);
        std::cout << "local filename: " << local_file << std::endl;

        if (DownloadFile(url, local_file)) {
            if (local_file.find(".tar.gz") != std::string::npos || local_file.find(".tar") != std::string::npos) {
                ExtractTarGz(local_file, runtime_dir);
            }
            remove(local_file.c_str());
        }
    }
}

// Function to execute a command
void ExecuteCommand(const std::string& command) {
#ifdef _WIN32
    system(command.c_str());
#else
    std::system(command.c_str());
#endif
}

int main() {
    // Determine the operating system
    std::string os_name;
#ifdef _WIN32
    os_name = "Windows";
#elif __linux__
    os_name = "Linux";
#elif __APPLE__
    os_name = "Darwin";
#else
    os_name = "Unknown";
#endif

    std::cout << "This computer is running " << os_name << "." << std::endl;

    // URLs for downloading JDK and JavaFX for different platforms
    std::map<std::string, std::vector<std::string> > os_urls;
    os_urls["Windows"].push_back("https://download.java.net/java/GA/jdk21.0.1/415e3f918a1f4062a0074a2794853d0d/12/GPL/openjdk-21.0.1_windows-x64_bin.zip");
    os_urls["Windows"].push_back("https://download.java.net/java/GA/javafx21.0.1/e5ab43c6aed54893b0840c1f2dcfca4d/GPL/openjfx-21.0.1_windows-x64_bin-sdk.zip");

    os_urls["Linux"].push_back("https://download.java.net/java/GA/jdk21.0.1/415e3f918a1f4062a0074a2794853d0d/12/GPL/openjdk-21.0.1_linux-x64_bin.tar.gz");
    os_urls["Linux"].push_back("https://download.java.net/java/GA/javafx21.0.1/e5ab43c6aed54893b0840c1f2dcfca4d/GPL/openjfx-21.0.1_linux-x64_bin-sdk.tar.gz");

    os_urls["Darwin"].push_back("https://download.java.net/java/GA/jdk21.0.1/415e3f918a1f4062a0074a2794853d0d/12/GPL/openjdk-21.0.1_macos-x64_bin.tar.gz");
    os_urls["Darwin"].push_back("https://download.java.net/java/GA/javafx21.0.1/e5ab43c6aed54893b0840c1f2dcfca4d/GPL/openjfx-21.0.1_macos-x64_bin-sdk.tar.gz");

    // Commands to run the JDK and JavaFX for different platforms
    std::map<std::string, std::string> os_commands;
    os_commands["Windows"] = "runtime\\jdk-21.0.1\\bin\\javaw.exe --module-path runtime\\javafx-sdk-21.0.1\\lib --add-modules javafx.controls,javafx.fxml,javafx.web -jar libs\\wave.jar";
    os_commands["Linux"] = "runtime/jdk-21.0.1/bin/java --module-path runtime/javafx-sdk-21.0.1/lib --add-modules javafx.controls,javafx.fxml,javafx.web -jar libs/wave.jar";
    os_commands["Darwin"] = "runtime/jdk-21.0.1.jdk/Contents/Home/bin/java --module-path runtime/javafx-sdk-21.0.1/lib --add-modules javafx.controls,javafx.fxml,javafx.web -jar libs/wave.jar";

    std::string runtime_dir = "runtime";
    if (!DirectoryExists(runtime_dir)) {
        if (CreateDirectory(runtime_dir)) {
            if (os_urls.find(os_name) != os_urls.end()) {
                std::cout << "Downloading Java runtime and JavaFX for " << os_name << "." << std::endl;
                DownloadAndExtract(os_urls[os_name], runtime_dir);
            }
        } else {
            std::cerr << "Failed to create directory: " << runtime_dir << std::endl;
            return 1;
        }
    } else {
        std::cout << "Java runtime and JavaFX already exist." << std::endl;
    }

    if (os_commands.find(os_name) != os_commands.end()) {
        std::cout << "Launching wavesignal on " << os_name << "." << std::endl;
        std::string command = os_commands[os_name];
        std::cout << "command: " << command << std::endl;
        ExecuteCommand(command);
    } else {
        std::cout << "This computer is running " << os_name << ", which is not specifically identified." << std::endl;
    }

    return 0;
}
