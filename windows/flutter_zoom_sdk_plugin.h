#ifndef FLUTTER_PLUGIN_FLUTTER_ZOOM_SDK_PLUGIN_H_
#define FLUTTER_PLUGIN_FLUTTER_ZOOM_SDK_PLUGIN_H_

#include <flutter/method_channel.h>
#include <flutter/plugin_registrar_windows.h>
#include <flutter/standard_method_codec.h>
#include <flutter/event_channel.h>
#include <flutter/event_sink.h>
#include <flutter/event_stream_handler_functions.h>

#include <map>
#include <memory>
#include <sstream>
#include <thread>
#include <future>
#include <vector>
#include <string>

#include <zoom_sdk.h>
#include <meeting_service_interface.h>
#include <auth_service_interface.h>
#include <setting_service_interface.h>
#include <meeting_service_components/meeting_ui_ctrl_interface.h>
#include <meeting_service_components/meeting_configuration_interface.h>
#include <meeting_service_components/meeting_participants_ctrl_interface.h>

namespace flutter_zoom_sdk {
	using flutter::EncodableList;
	using flutter::EncodableMap;
	using flutter::EncodableValue;
	using namespace std;

	struct ParticipantInfo
	{
		std::wstring userName;
		std::wstring customerKey;
		bool isHost;
		bool isVideoOn;
		bool isAudioMuted;
		bool isTalking;
		bool hasCamera;
	};

	class FlutterZoomSdkPlugin : public flutter::Plugin {
	public:
		static void RegisterWithRegistrar(flutter::PluginRegistrarWindows* registrar);

		FlutterZoomSdkPlugin();

		virtual ~FlutterZoomSdkPlugin();

		// Disallow copy and assign.
		FlutterZoomSdkPlugin(const FlutterZoomSdkPlugin&) = delete;
		FlutterZoomSdkPlugin& operator=(const FlutterZoomSdkPlugin&) = delete;

		unique_ptr<flutter::EventSink<>> meeting_event_sink_;

		void joinMeeting();

		bool startMeeting();

		flutter::EncodableList getParticipants();

	private:
		ZOOM_SDK_NAMESPACE::IAuthService* AuthService;
		ZOOM_SDK_NAMESPACE::IMeetingService* MeetingService;
		ZOOM_SDK_NAMESPACE::ISettingService* SettingService;

		// Keep meeting options from initAndJoin Zoom for onAuthenticationReturn in AuthEvent
		EncodableMap ZoomMeetingOptions;

		// Called when a method is called on this plugin's channel from Dart.
		void HandleMethodCall(
			const flutter::MethodCall<EncodableValue>& method_call,
			unique_ptr<flutter::MethodResult<EncodableValue>> result);

		void MeetingStreamListen(unique_ptr<flutter::EventSink<>>&& events);

		bool AuthorizeSDK(EncodableMap ZoomInitOptions);

		void createMeetingService();

		void createSettingService();

		bool leaveMeeting();

		bool hideMeeting();

		bool showMeeting();

		bool disableWindowStyles();

		void pressWinAndDownKeys();
	};

	class ZoomWindowHelper {
	 public:
	  static LRESULT CALLBACK
	  CustomWindowProc(HWND
	  hwnd,
	  UINT uMsg, WPARAM
	  wParam,
	  LPARAM lParam, UINT_PTR
	  uIdSubclass,
	  DWORD_PTR dwRefData
	  );
	  static void DisableWindowControls(HWND hWnd);

	  static void SetupZoomWindow(ZOOM_SDK_NAMESPACE::IMeetingService *pMeetingService);

	  static void SetWindowSizeAndPosition(HWND hWnd);
	};

	class ZoomParticipantsHelper {
	public:
	  static std::vector <ParticipantInfo> GetParticipantsList(ZOOM_SDK_NAMESPACE::IMeetingService *pMeetingService);
	};

	class AuthEvent : public ZOOM_SDK_NAMESPACE::IAuthServiceEvent {
	public:
		AuthEvent(const EncodableMap& zoomMeetingOptions);

		virtual ~AuthEvent();

	private:
		EncodableMap zoomMeetingOptions_;

		void onAuthenticationReturn(ZOOM_SDK_NAMESPACE::AuthResult ret);

		void onLoginReturnWithReason(ZOOM_SDK_NAMESPACE::LOGINSTATUS ret, ZOOM_SDK_NAMESPACE::IAccountInfo* pAccountInfo, ZOOM_SDK_NAMESPACE::LoginFailReason reason);

		void onLogout();

		void onZoomIdentityExpired();

		void onZoomAuthIdentityExpired();

		void onNotificationServiceStatus(ZOOM_SDK_NAMESPACE::SDKNotificationServiceStatus status);

		void onNotificationServiceStatus(ZOOM_SDK_NAMESPACE::SDKNotificationServiceStatus status, ZOOM_SDK_NAMESPACE::SDKNotificationServiceError error);
	};

	class MeetingServiceEvent : public ZOOM_SDK_NAMESPACE::IMeetingServiceEvent {
	public:
		MeetingServiceEvent();

		virtual ~MeetingServiceEvent();

	private:
		void onMeetingStatusChanged(ZOOM_SDK_NAMESPACE::MeetingStatus status, int iResult = 0);

		void onMeetingStatisticsWarningNotification(ZOOM_SDK_NAMESPACE::StatisticsWarningType type);

		void onMeetingParameterNotification(const ZOOM_SDK_NAMESPACE::MeetingParameter* meeting_param);

		void onSuspendParticipantsActivities();

		void onAICompanionActiveChangeNotice(bool bActive);
	};

}  // namespace flutter_zoom_sdk

#endif  // FLUTTER_PLUGIN_FLUTTER_ZOOM_SDK_PLUGIN_H_