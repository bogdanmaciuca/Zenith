#include "build.h"

#include <filesystem>
namespace fs = std::filesystem;

#include "result.h"

constexpr const char* ZN_EXTENSION = "zn";

Result<> Build(const std::string& src_dir) {
    fs::directory_entry src_dir_entry(src_dir);

    if (!src_dir_entry.exists()) {
        return Error("Directory " + src_dir + " does not exist!");
    }

    for (const auto& entry : fs::directory_iterator(src_dir_entry)) {
        if (!entry.is_regular_file()) {
            return Error(
                "File in source directory is not regular file: " +
                entry.path().filename().string()
            );
        }
        if (entry.path().extension() != ZN_EXTENSION) {
            return Error(
                "File in the source directory is of different type than *.zn: " +
                entry.path().filename().string()
            );
        }
    }
    
    return Result<>(true);
}
