/*
 * Copyright 2016 The Cartographer Authors
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "cartographer_ros/node_constants.h"

#include "glog/logging.h"

#include "gflags/gflags.h"

// 공유 gflags 정의 (1회만). node_main/offline_node/assets_writer_main에서는
// DECLARE로 참조한다. Lyrical(gflags 2.2)부터 중복 DEFINE이면 실행 즉시
// "defined more than once"로 죽는다 (issue-tracking 2026-10-28 §11).
DEFINE_bool(collect_metrics, false,
            "Activates the collection of runtime metrics. If activated, the "
            "metrics can be accessed via a ROS service.");
DEFINE_string(configuration_directory, "",
              "First directory in which configuration files are searched, "
              "second is always the Cartographer installation to allow "
              "including files from there.");
DEFINE_string(load_state_filename, "",
              "If non-empty, filename of a .pbstream file to load, containing "
              "a saved SLAM state.");
DEFINE_bool(load_frozen_state, true,
            "Load the saved state as frozen (non-optimized) trajectories.");
DEFINE_string(
    save_state_filename, "",
    "If non-empty, serialize state and write it to disk before shutting down.");
DEFINE_string(bag_filenames, "",
              "Comma-separated list of bags to process. One bag per trajectory. "
              "Any combination of simultaneous and sequential bags is supported.");
DEFINE_bool(use_bag_transforms, true,
            "Whether to read, use and republish transforms from bags.");

namespace cartographer_ros {

std::vector<std::string> ComputeRepeatedTopicNames(const std::string& topic,
                                                   const int num_topics) {
  CHECK_GE(num_topics, 0);
  if (num_topics == 1) {
    return {topic};
  }
  std::vector<std::string> topics;
  topics.reserve(num_topics);
  for (int i = 0; i < num_topics; ++i) {
    topics.emplace_back(topic + "_" + std::to_string(i + 1));
  }
  return topics;
}

}  // namespace cartographer_ros
