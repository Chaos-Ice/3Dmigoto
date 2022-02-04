#pragma once

#include <wrl.h>
#include <string>
#include <nvapi.h>

namespace Profiling {
    enum class Mode {
        NONE = 0,
        SUMMARY,
        TOP_COMMAND_LISTS,
        TOP_COMMANDS,
        CTO_WARNING,

        INVALID, // Must be last
    };

    class Overhead {
    public:
        LARGE_INTEGER cpu;
        unsigned count, hits;

        void clear();
    };

    struct State {
        LARGE_INTEGER start_time;
    };

    static inline void start(State *state)
    {
        QueryPerformanceCounter(&state->start_time);
    }

    static inline void end(State *state, Profiling::Overhead *overhead)
    {
        LARGE_INTEGER end_time;

        QueryPerformanceCounter(&end_time);
        overhead->cpu.QuadPart += end_time.QuadPart - state->start_time.QuadPart;
    }

    template<class T>
    static inline typename T::iterator lookup_map(T &map, typename T::key_type key, Profiling::Overhead *overhead)
    {
        Profiling::State state;

        if (Profiling::mode == Profiling::Mode::SUMMARY) {
            overhead->count++;
            Profiling::start(&state);
        }
        auto ret = map.find(key);
        if (Profiling::mode == Profiling::Mode::SUMMARY) {
            Profiling::end(&state, overhead);
            if (ret != end(map))
                overhead->hits++;
        }
        return ret;
    }

    void update_txt();
    void update_cto_warning(bool warn);
    void clear();

    extern Mode mode;
    extern Overhead present_overhead;
    extern Overhead overlay_overhead;
    extern Overhead draw_overhead;
    extern Overhead map_overhead;
    extern Overhead hash_tracking_overhead;
    extern Overhead stat_overhead;
    extern Overhead shaderregex_overhead;
    extern Overhead cursor_overhead;
    extern Overhead nvapi_overhead;
    extern std::wstring text;
    extern std::wstring cto_warning;
    extern INT64 interval;
    extern bool freeze;

    extern Overhead shader_hash_lookup_overhead;
    extern Overhead shader_reload_lookup_overhead;
    extern Overhead shader_original_lookup_overhead;
    extern Overhead shaderoverride_lookup_overhead;
    extern Overhead texture_handle_info_lookup_overhead;
    extern Overhead textureoverride_lookup_overhead;
    extern Overhead resource_pool_lookup_overhead;

    extern unsigned resource_full_copies;
    extern unsigned resource_reference_copies;
    extern unsigned stereo2mono_copies;
    extern unsigned msaa_resolutions;
    extern unsigned buffer_region_copies;
    extern unsigned surfaces_cleared;
    extern unsigned resources_created;
    extern unsigned resource_pool_swaps;
    extern unsigned max_copies_per_frame_exceeded;
    extern unsigned injected_draw_calls;
    extern unsigned skipped_draw_calls;
    extern unsigned max_executions_per_frame_exceeded;
    extern unsigned iniparams_updates;

    // NvAPI profiling:

#define NVAPI_PROFILE_PREFIX \
Profiling::State state; \
if (Profiling::mode == Profiling::Mode::SUMMARY) \
    Profiling::start(&state); \
auto ret =

#define NVAPI_PROFILE_SUFFIX \
if (Profiling::mode == Profiling::Mode::SUMMARY) \
    Profiling::end(&state, &Profiling::nvapi_overhead); \
return ret;

    static inline NvAPI_Status NvAPI_Stereo_Enable(void)
    {
        NVAPI_PROFILE_PREFIX
        ::NvAPI_Stereo_Enable();
        NVAPI_PROFILE_SUFFIX
    }
    static inline NvAPI_Status NvAPI_Stereo_IsEnabled(NvU8 *pIsStereoEnabled)
    {
        NVAPI_PROFILE_PREFIX
        ::NvAPI_Stereo_IsEnabled(pIsStereoEnabled);
        NVAPI_PROFILE_SUFFIX
    }
    static inline NvAPI_Status NvAPI_Stereo_IsActivated(StereoHandle stereoHandle, NvU8 *pIsStereoOn)
    {
        NVAPI_PROFILE_PREFIX
        ::NvAPI_Stereo_IsActivated(stereoHandle, pIsStereoOn);
        NVAPI_PROFILE_SUFFIX
    }
    static inline NvAPI_Status NvAPI_Stereo_GetEyeSeparation(StereoHandle hStereoHandle, float *pSeparation)
    {
        NVAPI_PROFILE_PREFIX
        ::NvAPI_Stereo_GetEyeSeparation(hStereoHandle, pSeparation);
        NVAPI_PROFILE_SUFFIX
    }
    static inline NvAPI_Status NvAPI_Stereo_GetSeparation(StereoHandle stereoHandle, float *pSeparationPercentage)
    {
        NVAPI_PROFILE_PREFIX
        ::NvAPI_Stereo_GetSeparation(stereoHandle, pSeparationPercentage);
        NVAPI_PROFILE_SUFFIX
    }
    static inline NvAPI_Status NvAPI_Stereo_SetSeparation(StereoHandle stereoHandle, float newSeparationPercentage)
    {
        NVAPI_PROFILE_PREFIX
        ::NvAPI_Stereo_SetSeparation(stereoHandle, newSeparationPercentage);
        NVAPI_PROFILE_SUFFIX
    }
    static inline NvAPI_Status NvAPI_Stereo_GetConvergence(StereoHandle stereoHandle, float *pConvergence)
    {
        NVAPI_PROFILE_PREFIX
        ::NvAPI_Stereo_GetConvergence(stereoHandle, pConvergence);
        NVAPI_PROFILE_SUFFIX
    }
    static inline NvAPI_Status NvAPI_Stereo_SetConvergence(StereoHandle stereoHandle, float newConvergence)
    {
        NVAPI_PROFILE_PREFIX
        ::NvAPI_Stereo_SetConvergence(stereoHandle, newConvergence);
        NVAPI_PROFILE_SUFFIX
    }
    static inline NvAPI_Status NvAPI_Stereo_SetActiveEye(StereoHandle hStereoHandle, NV_STEREO_ACTIVE_EYE StereoEye)
    {
        NVAPI_PROFILE_PREFIX
        ::NvAPI_Stereo_SetActiveEye(hStereoHandle, StereoEye);
        NVAPI_PROFILE_SUFFIX
    }
    static inline NvAPI_Status NvAPI_Stereo_ReverseStereoBlitControl(StereoHandle hStereoHandle, NvU8 TurnOn)
    {
        NVAPI_PROFILE_PREFIX
        ::NvAPI_Stereo_ReverseStereoBlitControl(hStereoHandle, TurnOn);
        NVAPI_PROFILE_SUFFIX
    }
    static inline NvAPI_Status NvAPI_Stereo_SetSurfaceCreationMode(__in StereoHandle hStereoHandle, __in NVAPI_STEREO_SURFACECREATEMODE creationMode)
    {
        NVAPI_PROFILE_PREFIX
        ::NvAPI_Stereo_SetSurfaceCreationMode(hStereoHandle, creationMode);
        NVAPI_PROFILE_SUFFIX
    }
    static inline NvAPI_Status NvAPI_Stereo_GetSurfaceCreationMode(__in StereoHandle hStereoHandle, __in NVAPI_STEREO_SURFACECREATEMODE* pCreationMode)
    {
        NVAPI_PROFILE_PREFIX
        ::NvAPI_Stereo_GetSurfaceCreationMode(hStereoHandle, pCreationMode);
        NVAPI_PROFILE_SUFFIX
    }
    static inline NvAPI_Status NvAPI_DISP_GetDisplayConfig(__inout NvU32 *pathInfoCount, __out_ecount_full_opt(*pathInfoCount) NV_DISPLAYCONFIG_PATH_INFO *pathInfo)
    {
        NVAPI_PROFILE_PREFIX
        ::NvAPI_DISP_GetDisplayConfig(pathInfoCount, pathInfo);
        NVAPI_PROFILE_SUFFIX
    }
#if defined(_D3D9_H_) || defined(__d3d10_h__) || defined(__d3d11_h__)
    static inline NvAPI_Status NvAPI_D3D_GetCurrentSLIState(IUnknown *pDevice, NV_GET_CURRENT_SLI_STATE *pSliState)
    {
        NVAPI_PROFILE_PREFIX
        ::NvAPI_D3D_GetCurrentSLIState(pDevice, pSliState);
        NVAPI_PROFILE_SUFFIX
    }
#endif

#undef NVAPI_PROFILE_PREFIX
#undef NVAPI_PROFILE_SUFFIX
}
