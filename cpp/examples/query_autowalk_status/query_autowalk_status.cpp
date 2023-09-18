/**
 * Copyright (c) 2023 Boston Dynamics, Inc.  All rights reserved.
 *
 * Downloading, reproducing, distributing or otherwise using the SDK Software
 * is subject to the terms and conditions of the Boston Dynamics Software
 * Development Kit License (20191101-BDSDK-SL).
 */


#include <CLI/CLI.hpp>

#include "autowalk_player.hpp"

int main(int argc, char** argv) {
    // Initialize variables
    std::filesystem::path walk_folder;
    std::string mission_name;
    std::chrono::seconds pause_duration;
    bool fail_on_mission_question;

    // Parse command line arguements
    CLI::App parser{"QueryAutowalkStatus"};
    ::bosdyn::client::CommonCLIArgs common_args;
    ::bosdyn::client::AddCommonArguments(parser, common_args);
    parser.add_option("--walk_folder", walk_folder, "Autowalk mission folder")->required();
    parser.add_option("--mission_name", mission_name, "Mission to upload from walk folder.")
        ->default_val("");
    parser
        .add_option("--mission_pause_duration", pause_duration, "Mission client pause_duration (s)")
        ->default_val(3);
    parser
        .add_option("--fail_on_mission_question", fail_on_mission_question,
                    "If mission question(s) arise, script will print question(s) then quit")
        ->default_val(false);
    CLI11_PARSE(parser, argc, argv);

    // Determine mission name
    // Prior to 3.3 autowalk files were named "autogenerated.walk" by default.
    // Post 3.3 autowalk files are named after the map name by default.
    // If the mission name is not specified first we try using the map name then we try using
    // "autogenerated.walk"
    if (mission_name.empty()) {
        ::bosdyn::common::Status get_walk_path_status = GetMissionName(walk_folder, &mission_name);
        if (!get_walk_path_status) {
            std::cerr << get_walk_path_status.DebugString() << std::endl;
            return 1;
        }
    }

    // Make sure path to walk file is valid.
    std::filesystem::path walk_path = walk_folder / ::bosdyn::common::kMissionsDir / mission_name;
    if (!std::filesystem::exists(walk_path)) {
        std::cerr << std::string(walk_path) + " does not exist in the filesystem." << std::endl;
        return 1;
    }

    // Initialize autowalk player
    AutowalkPlayer autowalk_player;
    auto init_status = autowalk_player.Init(common_args);
    if (!init_status) {
        std::cerr << init_status.DebugString() << std::endl;
        return 1;
    }

    // Upload graph nav map
    auto upload_status = autowalk_player.UploadGraphAndSnapshots(walk_folder);
    if (!upload_status) {
        std::cerr << upload_status.DebugString() << std::endl;
        return 1;
    }
    // Load autowalk
    auto load_status = autowalk_player.LoadAutowalk(walk_path);
    if (!load_status) {
        std::cerr << load_status.DebugString() << std::endl;
        return 1;
    }

    // Play autowalk
    auto play_status = autowalk_player.PlayAutowalk(pause_duration, fail_on_mission_question);
    if (!play_status) {
        std::cerr << play_status.DebugString() << std::endl;
        return 1;
    }

    std::cout << "------Query Autowalk Status Application Worked as Expected!" << std::endl;
    return 0;
}
