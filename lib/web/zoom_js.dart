@JS()
library zoom_helper;

import 'package:js/js.dart';

/// Initial Parameter Required For Zoom Web
@JS()
@anonymous

/// needed along with factory constructor
class InitParams {
  external factory InitParams(
      {leaveUrl,
      helper,
      debug,
      showMeetingHeader,
      disableInvite,
      disableCallOut,
      disableRecord,
      disableJoinAudio,
      audioPanelAlwaysOpen,
      isSupportAV,
      isSupportChat,
      isSupportQA,
      isSupportCC,
      isSupportPolling,
      isSupportBreakout,
      screenShare,
      rwcBackup,
      videoDrag,
      sharingMode,
      videoHeader,
      isLockBottom,
      isSupportNonverbal,
      isShowJoiningErrorDialog,
      disablePreview,
      disableCORP,
      inviteUrlFormat,
      disableVoIP,
      disableReport,
      meetingInfo,
      success,
      error});
  external String get leaveUrl;
}

/// Join Meeting helper
@JS()
@anonymous

/// needed along with factory constructor
class JoinParams {
  external factory JoinParams(
      {meetingNumber, userName, userEmail, signature, sdkKey, passWord, success, error});
}

/// Signature helper
@JS()
@anonymous

/// needed along with factory constructor
class SignatureParams {
  external factory SignatureParams({meetingNumber, apiKey, apiSecret, role});
}

/// meeting status helper
@JS()
@anonymous
class MeetingStatus {
  external factory MeetingStatus({int meetingStatus});
  external int get meetingStatus;
}

@JS()
@anonymous
class ShowJoinAudioParams {
  /// bool
  external factory ShowJoinAudioParams({show});
}

@JS()
@anonymous
class LeaveParams {
  external factory LeaveParams({success, error});
}

@JS()
@anonymous
class MuteParams {
  external factory MuteParams({userId, mute});
}

/// Basic Zoom SDK Web Functions helper
@JS()
class ZoomMtg {
  external static void setZoomJSLib(String path, String dir);
  external static final i18n;
  external static void preLoadWasm();
  external static void prepareWebSDK();
  external static void prepareJssdk();
  external static void init(InitParams initParams);
  external static void join(JoinParams joinParams);
  external static void mute(MuteParams params);

  @JS('getAttendeeslist')
  external static dynamic getAttendeeslist();

  external static void showJoinAudioFunction(ShowJoinAudioParams params);
  external static void leaveMeeting(LeaveParams params);
  external static String generateSDKSignature(SignatureParams signatureParams);
  external static dynamic checkSystemRequirements();
  external static void inMeetingServiceListener(
      String event, Function(MeetingStatus?) callback);
}
