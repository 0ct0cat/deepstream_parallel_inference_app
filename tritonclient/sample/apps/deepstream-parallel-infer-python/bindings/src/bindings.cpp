#include "deepstream_common.h"
#include "deepstream_config.h"
#include "deepstream_config_yaml.h"
#include "deepstream_dsanalytics.h"
#include "deepstream_parallel_infer.h"
#include "deepstream_primary_gie.h"
#include "deepstream_secondary_gie.h"
#include "deepstream_secondary_preprocess.h"

#include <Python.h>
#include <pybind11/pybind11.h>

#include <glib.h>
#include <gst/gst.h>
#include <yaml-cpp/yaml.h>

GST_DEBUG_CATEGORY(NVDS_APP);

namespace py = pybind11;
// create_primary_gie_bin
// create_dsanalytics_bin
// create_dsexample_bin
// create_osd_bin
// create_preprocess_bin
// create_tiled_display_bin
// create_tracking_bin
// create_segvisual_bin
// set_streammux_properties
// =====================
// create_secondary_gie_bin && destroy_secondary_gie_bin
// create_secondary_preprocess_bin && destroy_secondary_preprocess_bin
// =====================
// create_sink_bin && create_demux_sink_bin && set_rtsp_udp_port_num
// ====================
// create_source_bin && create_audio_source_bin &&
// create_multi_source_bin && create_nvmultiurisrcbin_bin &&
// reset_source_pipeline && set_source_to_playing && reset_encodebin &&
// destroy_smart_record_bin
// =====================
PYBIND11_MODULE(pyds_common, m) {
  m.def(
      "create_primary_gie_bin",
      [](const char *group, char *config_path) {
        NvDsGieConfig config;
        NvDsPrimaryGieBin *bin = nullptr;
        if (parse_gie_yaml(&config, group, config_path)) {
          bin = (NvDsPrimaryGieBin *)g_malloc0(sizeof(NvDsPrimaryGieBin));
          if (!create_primary_gie_bin(&config, bin)) {
            g_printerr("Error: create_primary_gie_bin failed \n");
          }
        } else {
          g_printerr("Error: parse_gie_yaml failed \n");
        }
        return py::capsule(bin, [](void *bin) {
          if (bin != nullptr)
            g_free(bin);
        });
      },
      "create_primary_gie_bin");

  m.def(
      "create_dsanalytics_bin",
      [](char *config_path) {
        NvDsDsAnalyticsConfig config;
        NvDsDsAnalyticsBin *bin = nullptr;
        if (parse_dsanalytics_yaml(&config, config_path)) {
          bin = (NvDsDsAnalyticsBin *)g_malloc0(sizeof(NvDsDsAnalyticsBin));
          if (!create_dsanalytics_bin(&config, bin)) {
            g_printerr("Error: create_dsanalytics_bin failed \n");
          }
        } else {
          g_printerr("Error: parse_dsanalytics_yaml failed \n");
        }
        return py::capsule(bin, [](void *bin) {
          if (bin != nullptr)
            g_free(bin);
        });
      },
      "create_dsanalytics_bin");

  m.def(
      "create_dsexample_bin",
      [](char *config_path) {
        NvDsDsExampleConfig config;
        NvDsDsExampleBin *bin = nullptr;
        if (parse_dsexample_yaml(&config, config_path)) {
          bin = (NvDsDsExampleBin *)g_malloc0(sizeof(NvDsDsExampleBin));
          if (!create_dsexample_bin(&config, bin)) {
            g_printerr("Error: create_dsexample_bin failed \n");
          }
        } else {
          g_printerr("Error: parse_dsexample_yaml failed \n");
        }
        return py::capsule(bin, [](void *bin) {
          if (bin != nullptr)
            g_free(bin);
        });
      },
      "create_dsexample_bin");

  m.def(
      "create_osd_bin",
      [](char *config_path) {
        NvDsOSDConfig config;
        NvDsOSDBin *bin = nullptr;
        if (parse_osd_yaml(&config, config_path)) {
          bin = (NvDsOSDBin *)g_malloc0(sizeof(NvDsOSDBin));
          if (!create_osd_bin(&config, bin)) {
            g_printerr("Error: create_osd_bin failed \n");
          }
        } else {
          g_printerr("Error: parse_osd_yaml failed \n");
        }
        return py::capsule(bin, [](void *bin) {
          if (bin != nullptr)
            g_free(bin);
        });
      },
      "create_osd_bin");

  m.def(
      "create_preprocess_bin",
      [](char *config_path) {
        NvDsPreProcessConfig config;
        NvDsPreProcessBin *bin = nullptr;
        if (parse_preprocess_yaml(&config, config_path)) {
          bin = (NvDsPreProcessBin *)g_malloc0(sizeof(NvDsPreProcessBin));
          if (!create_preprocess_bin(&config, bin)) {
            g_printerr("Error: create_preprocess_bin failed \n");
          }
        } else {
          g_printerr("Error: parse_preprocess_yaml failed \n");
        }
        return py::capsule(bin, [](void *bin) {
          if (bin != nullptr)
            g_free(bin);
        });
      },
      "create_preprocess_bin");

  m.def(
      "create_tiled_display_bin",
      [](char *config_path) {
        NvDsTiledDisplayConfig config;
        NvDsTiledDisplayBin *bin = nullptr;
        if (parse_tiled_display_yaml(&config, config_path)) {
          bin = (NvDsTiledDisplayBin *)g_malloc0(sizeof(NvDsTiledDisplayBin));
          if (!create_tiled_display_bin(&config, bin)) {
            g_printerr("Error: create_tiled_display_bin failed \n");
          }
        } else {
          g_printerr("Error: parse_tiled_display_yaml failed \n");
        }
        return py::capsule(bin, [](void *bin) {
          if (bin != nullptr)
            g_free(bin);
        });
      },
      "create_tiled_display_bin");

  m.def(
      "create_tracking_bin",
      [](char *config_path) {
        NvDsTrackerConfig config;
        NvDsTrackerBin *bin = nullptr;
        if (parse_tracker_yaml(&config, config_path)) {
          bin = (NvDsTrackerBin *)g_malloc0(sizeof(NvDsTrackerBin));
          if (!create_tracking_bin(&config, bin)) {
            g_printerr("Error: create_tracking_bin failed \n");
          }
        } else {
          g_printerr("Error: parse_tracker_yaml failed \n");
        }
        return py::capsule(bin, [](void *bin) {
          if (bin != nullptr)
            g_free(bin);
        });
      },
      "create_tracking_bin");

  m.def(
      "create_segvisual_bin",
      [](char *config_path) {
        NvDsSegVisualConfig config;
        NvDsSegVisualBin *bin = nullptr;
        if (parse_segvisual_yaml(&config, config_path)) {
          bin = (NvDsSegVisualBin *)g_malloc0(sizeof(NvDsSegVisualBin));
          if (!create_segvisual_bin(&config, bin)) {
            g_printerr("Error: create_segvisual_bin failed \n");
          }
        } else {
          g_printerr("Error: parse_segvisual_yaml failed \n");
        }
        return py::capsule(bin, [](void *bin) {
          if (bin != nullptr)
            g_free(bin);
        });
      },
      "create_segvisual_bin");

  m.def(
      "set_streammux_properties",
      [](GstElement *streammux, char *config_path) {
        NvDsStreammuxConfig config;
        if (parse_streammux_yaml(&config, config_path)) {
          if (!set_streammux_properties(&config, streammux)) {
            g_printerr("Error: set_streammux_properties failed \n");
          }
        } else {
          g_printerr("Error: parse_streammux_yaml failed \n");
        }
      },
      "set_streammux_properties");

  m.def(
      "create_secondary_gie_bin",
      [](guint primary_gie_unique_id, char *config_path) {
        std::string sgie_str = "secondary-gie";
        NvDsGieConfig configArray[MAX_SECONDARY_GIE_BINS];
        NvDsSecondaryGieBin *bin = nullptr;
        const auto nodes = YAML::LoadFile(config_path);
        int count = 0;
        for (const auto &node : nodes) {
          const auto &key = node.first.as<std::string>();
          if (key.compare(0, sgie_str.size(), sgie_str) == 0) {
            if (!parse_gie_yaml(&configArray[count], key, config_path)) {
              g_printerr("Error: sgie parse_gie_yaml failed \n");
              goto error;
            }
            if (configArray[count].enable) {
              if (count++ >= MAX_SECONDARY_GIE_BINS) {
                g_printerr("Error: too many sgies \n");
                goto error;
              }
            }
          }
        }
        bin = (NvDsSecondaryGieBin *)g_malloc0(sizeof(NvDsSecondaryGieBin));
        if (!create_secondary_gie_bin(count, primary_gie_unique_id, configArray,
                                      bin)) {
          g_printerr("Error: create_secondary_gie_bin failed \n");
        }
      error:
        return py::capsule(bin, [](void *bin) {
          if (bin != nullptr) {
            destroy_secondary_gie_bin((NvDsSecondaryGieBin *)bin);
            g_free(bin);
          }
        });
      },
      "create_secondary_gie_bin");

  m.def(
      "create_secondary_preprocess_bin",
      [](guint primary_gie_unique_id, char *config_path) {
        std::string spreprocess_str = "secondary-pre-process";
        NvDsPreProcessConfig configArray[MAX_SECONDARY_PREPROCESS_BINS];
        NvDsSecondaryPreProcessBin *bin = nullptr;
        const auto nodes = YAML::LoadFile(config_path);
        int count = 0;
        for (const auto &node : nodes) {
          const auto &key = node.first.as<std::string>();
          if (key.compare(0, spreprocess_str.size(), spreprocess_str) == 0) {
            if (!parse_preprocess_yaml(&configArray[count], config_path)) {
              g_printerr("Error: parse_preprocess_yaml failed \n");
              goto error;
            }
            if (configArray[count].enable) {
              if (count++ >= MAX_SECONDARY_GIE_BINS) {
                g_printerr("Error: too many sgies \n");
                goto error;
              }
            }
          }
        }
        bin = (NvDsSecondaryPreProcessBin *)g_malloc0(
            sizeof(NvDsSecondaryPreProcessBin));
        if (!create_secondary_preprocess_bin(count, primary_gie_unique_id,
                                             configArray, bin)) {
          g_printerr("Error: create_secondary_preprocess_bin failed \n");
        }
      error:
        return py::capsule(bin, [](void *bin) {
          if (bin != nullptr) {
            destroy_secondary_preprocess_bin((NvDsSecondaryPreProcessBin *)bin);
            g_free(bin);
          }
        });
      },
      "create_secondary_preprocess_bin");

  m.def(
      "set_metamux_properties",
      [](GstElement *metamux, char *config_path) {
        NvDsMetaMuxConfig config;
        if (!parse_metamux_yaml(&config, config_path)) {
          if (config.enable) {
            g_object_set(G_OBJECT(metamux), "config-file",
                         GET_FILE_PATH(config.config_file_path), NULL);
          }
        } else {
          g_printerr("Error: parse_streammux_yaml failed \n");
        }
      },
      "set_metamux_properties");
}