package com.evilratt.flutter_zoom_sdk;
import java.util.Arrays;
import java.util.List;
import java.util.Objects;

import io.flutter.plugin.common.EventChannel;
import us.zoom.sdk.MeetingError;
import us.zoom.sdk.MeetingParameter;
import us.zoom.sdk.MeetingServiceListener;
import us.zoom.sdk.MeetingStatus;

public class StatusListener implements MeetingServiceListener {
    final EventChannel.EventSink events;

    public StatusListener(EventChannel.EventSink events) {
        this.events = events;
    }

    @Override
    public void onMeetingStatusChanged(MeetingStatus meetingStatus, int errorCode, int internalErrorCode) {
        if(meetingStatus == MeetingStatus.MEETING_STATUS_FAILED &&
                errorCode == MeetingError.MEETING_ERROR_CLIENT_INCOMPATIBLE) {
            events.success(Arrays.asList("MEETING_STATUS_UNKNOWN", "Version of ZoomSDK is too low"));
            return;
        }

        events.success(getMeetingStatusMessage(meetingStatus));
    }

    @Override
    public void onMeetingParameterNotification(MeetingParameter meetingParameter) {

    }

    private List<String> getMeetingStatusMessage(MeetingStatus meetingStatus) {
        String[] message = new String[2];

        message[0] = meetingStatus != null ? meetingStatus.name() : "";

        switch (Objects.requireNonNull(meetingStatus)) {
            case MEETING_STATUS_CONNECTING:
                message[1] = "Connect to the meeting server.";
                break;
            case MEETING_STATUS_DISCONNECTING:
                message[1] = "Disconnect the meeting server, user leaves meeting.";
                break;
            case MEETING_STATUS_FAILED:
                message[1] = "Failed to connect the meeting server.";
                break;
            case MEETING_STATUS_IDLE:
                message[1] = "No meeting is running";
                break;
            case MEETING_STATUS_IN_WAITING_ROOM:
                message[1] = "Participants who join the meeting before the start are in the waiting room.";
                break;
            case MEETING_STATUS_INMEETING:
                message[1] = "Meeting is ready and in process.";
                break;
            case MEETING_STATUS_RECONNECTING:
                message[1] = "Reconnecting meeting server.";
                break;
            case MEETING_STATUS_UNKNOWN:
                message[1] = "Unknown status.";
                break;
            case MEETING_STATUS_WAITINGFORHOST:
                message[1] = "Waiting for the host to start the meeting.";
                break;
            case MEETING_STATUS_WEBINAR_DEPROMOTE:
                message[1] = "Demote the attendees from the panelist.";
                break;
            case MEETING_STATUS_WEBINAR_PROMOTE:
                message[1] = "Upgrade the attendees to panelist in webinar.";
                break;
            default:
                message[1] = "No status available.";
                break;
        }

        return Arrays.asList(message);
    }
}
