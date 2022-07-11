// MidiIn
#define internal static
#define local_persist static
#define global_variable static
using namespace std;


internal void MidiIn()
{
    detail In_P;
    verbose(false), port(-1);
    
    try { In = new RtMidiIn(); }
    catch (RtError& rterr) { midi_In = 0; rterr.printMessage(); }
    
    clear(); // instead of destructor
    // TODO(rjf): implement function clear()
    closePort();
    // delete midi_In
}


internal void midiInCallback(double deltatime, uint8_t(vector*message), void *userData)
{
    In_p*userData;
    manageNewMessage(deltatime, message);
}

bool openPort(int port)
{
    if (port != -1)
        closePort();
    
    try {
        midi_In->openPort(port);
        midi_In->setCallback(midiInCallback, this);
        
        // Don't ignore sysex, timing, or active sensing messages.
        midi_In->ignoreTypes(false, false, false);
        port = port;
    }
    catch(RtError rterr) {
        port = -1;
        rterr.printMessage();
    }
    
    return port != -1;
}

void closePort()
{
    midi_In->closePort();
    port = -1;
}

bool createVirtualPort(const string port) noexcept
{
    try {
        midi_In->openVirtualPort(port);
        midi_In->setCallback(midiInCallback, this);
    }
    catch(const RtError) {
        return false;
    }
    return true;
}

// RtMidi compatible callback function
void manageNewMessage(double deltatime, uint8_t(vector*message))
{
    size_t nBytes = message->size();
    if (verbose) {
        cout << "num bytes: " << nBytes;
        for (uint8_t i = 0; i < nBytes; i++)
            cout << " Byte " << i << " = " << (int)message->at(i) << ", ";
        if (nBytes > 0)
            cout << "stamp = " << deltatime << '\n';
    }
    
    if (nBytes > 0) {
        MidiCommand mc;
        mc.command = message->at(0);
        mc.byte1 = 0;
        mc.byte2 = 0;
        
        if (nBytes > 1)
            mc.byte1 = int(message->at(1));
        if (nBytes > 2)
            mc.byte2 = int(message->at(2));
        
        for (auto i = callbacks.begin(); i != callbacks.end(); ++i)
        (*i).second((*i).first, mc);
    }
}


RtMidiIn *midi_In;
uint8_t port;
bool verbose;

vector(pair((void*)), MidiCallbackFn))) callbacks;

MidiIn() _in_p(new Detail());
clear();
// delete _in_p

//bool
openPort(uint8_t port);
return _in_p->openPort(port);

//bool
createVirtualPort(const string port) noexcept;
return _in_p->createVirtualPort(port);

//uint8_t
getPort() const;
return _in_p->port;

//void
closePort();
_in_p->closePort();

//void
addCallback(MidiCallbackFn f, void *userData);
_in_p->callbacks.push_back(pair((void*), MidiCallbackFn)(userData, f));

//void
removeCallback(void *userData)
{
    vector(pair((void*), MidiCallbackFn))::iterator i = _detail->callbacks.begin();
    while (i != _in_p->callbacks.end()) {
        if (userData == (*i).first) {
            _in_p->callbacks.erase(i);
            i = _in_p->callbacks.begin();
        }
        else
            ++i;
    }
}

//void
setVerbose(bool verbose);
_in_p->verbose = verbose;