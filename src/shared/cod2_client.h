#ifndef COD2_CLIENT_H
#define COD2_CLIENT_H


// https://github.com/id-Software/Enemy-Territory/blob/40342a9e3690cb5b627a433d4d5cbf30e3c57698/src/game/q_shared.h#L1621
enum clientState_e{
	CLIENT_STATE_DISCONNECTED,    // not talking to a server
	CLIENT_STATE_CINEMATIC,       // playing a cinematic or a static pic, not connected to a server
	CLIENT_STATE_AUTHORIZING,     // not used any more, was checking cd key
	CLIENT_STATE_CONNECTING,      // sending request packets to the server
	CLIENT_STATE_CHALLENGING,     // sending challenge packets to the server
	CLIENT_STATE_CONNECTED,       // netchan_t established, getting gamestate
	CLIENT_STATE_LOADING,         // only during cgame initialization, never during main loop
	CLIENT_STATE_PRIMED,          // got gamestate, waiting for first frame
	CLIENT_STATE_ACTIVE,          // game views should be displayed       
};

inline const char* get_client_state_name(int state) {
    switch (state) {
        case CLIENT_STATE_DISCONNECTED: return "DISCONNECTED";
        case CLIENT_STATE_CINEMATIC: return "CINEMATIC";
        case CLIENT_STATE_AUTHORIZING: return "AUTHORIZING";
        case CLIENT_STATE_CONNECTING: return "CONNECTING";
        case CLIENT_STATE_CHALLENGING: return "CHALLENGING";
        case CLIENT_STATE_CONNECTED: return "CONNECTED";
        case CLIENT_STATE_LOADING: return "LOADING";
        case CLIENT_STATE_PRIMED: return "PRIMED";
        case CLIENT_STATE_ACTIVE: return "ACTIVE";
        default: return "UNKNOWN";
    }
}


#endif