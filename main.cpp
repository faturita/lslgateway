#include <QCoreApplication>

#include <lsl_cpp.h>
#include <stdlib.h>
using namespace lsl;

/**
 * This is an example of how a simple data stream can be offered on the network.
 * Here, the stream is named SimpleStream, has content-type EEG, and 128 channels.
 * The transmitted samples contain random numbers (and the sampling rate is irregular
 * and effectively bounded by the speed at which the program can push out samples).
 */

int sending() {

    // make a new stream_info (128ch) and open an outlet with it
    stream_info info("SimpleStream","EEG",128);
    stream_outlet outlet(info);

    // send data forever
    float sample[128];
    while(true) {
        // generate random data
        for (int c=0;c<128;c++)
            sample[c] = (rand()%1500)/500.0-1.5;
        // send it
        outlet.push_sample(sample);
    }

    return 0;
}

/**
 * This is a minimal example that demonstrates how a multi-channel stream (here 128ch)
 * of a particular name (here: SimpleStream) can be resolved into an inlet, and how the
 * raw sample data & time stamps are pulled from the inlet. This example does not
 * display the obtained data.
 *
 */

int forwarding() {
    using namespace lsl;

    stream_info info("openvibeSignal","EEG",11);
    stream_outlet outlet(info);

    // resolve the stream of interest & make an inlet to get data from the first result
    std::vector<stream_info> markers = resolve_stream("name","openvibeMarkers2");
    stream_inlet markersInlet(markers[0]);

    std::vector<stream_info> results = resolve_stream("name","openvibeSignal2");
    stream_inlet inlet(results[0]);

    // receive data & time stamps forever (not displaying them here)
    float sample[8];
    float marker;

    float forwardsample[11];

    while (true)
    {
        double ts = inlet.pull_sample(&sample[0],8);
        printf ("%10.8f:%10.8f\n",ts,sample[0]);

        forwardsample[0] = ts;
        for(int i=0;i<8;i++)
        {
            forwardsample[i+1] = sample[i];
        }
        forwardsample[9] = 0;
        forwardsample[10] = 0;

        double mts = markersInlet.pull_sample(&marker,1,0.0f);
        if (mts>0)
        {
            printf ("%10.8f:Marker %10.8f\n",mts,marker);
            forwardsample[9] = mts;
            forwardsample[10] = marker;
        }

        outlet.push_sample(forwardsample);
    }

    return 0;
}

int receiving() {
    using namespace lsl;

    std::vector<stream_info> results = resolve_stream("name","openvibeSignal");
    stream_inlet inlet(results[0]);

    // receive data & time stamps forever (not displaying them here)
    float sample[10];
    float marker;
    while (true)
    {
        double ts = inlet.pull_sample(&sample[0],10);
        printf ("%10.8f:%10.8f\n",ts,sample[9]);

    }

    return 0;
}

/**
 * @brief main
 * @param argc
 * @param argv
 * @return
 * export LD_LIBRARY_PATH=/Users/user/work/labstreaminglayer/build/install/lsl_Release/LSL/lib/
 */
int main(int argc, char *argv[])
{
    forwarding();
    return 0;

}
