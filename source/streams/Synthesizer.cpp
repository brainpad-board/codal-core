/*
The MIT License (MIT)

Copyright (c) 2017 Lancaster University.

Permission is hereby granted, free of charge, to any person obtaining a
copy of this software and associated documentation files (the "Software"),
to deal in the Software without restriction, including without limitation
the rights to use, copy, modify, merge, publish, distribute, sublicense,
and/or sell copies of the Software, and to permit persons to whom the
Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
DEALINGS IN THE SOFTWARE.
*/

#include "Synthesizer.h"
#include "CodalFiber.h"
#include "ErrorNo.h"

using namespace codal;

const uint16_t Synthesizer::SineTone[TONE_WIDTH] = {0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,2,2,2,3,3,3,4,4,5,5,6,6,7,7,8,8,9,9,10,11,11,12,13,13,14,15,16,16,17,18,19,20,21,22,22,23,24,25,26,27,28,29,30,32,33,34,35,36,37,38,40,41,42,43,45,46,47,49,50,51,53,54,56,57,58,60,61,63,64,66,68,69,71,72,74,76,77,79,81,82,84,86,87,89,91,93,95,96,98,100,102,104,106,108,110,112,114,116,118,120,122,124,126,128,130,132,134,136,138,141,143,145,147,149,152,154,156,158,161,163,165,167,170,172,175,177,179,182,184,187,189,191,194,196,199,201,204,206,209,211,214,216,219,222,224,227,229,232,235,237,240,243,245,248,251,253,256,259,262,264,267,270,273,275,278,281,284,287,289,292,295,298,301,304,307,309,312,315,318,321,324,327,330,333,336,339,342,345,348,351,354,357,360,363,366,369,372,375,378,381,384,387,390,393,396,399,402,405,408,411,414,417,420,424,427,430,433,436,439,442,445,448,452,455,458,461,464,467,470,473,477,480,483,486,489,492,495,498,502,505,508,511,514,517,520,524,527,530,533,536,539,542,545,549,552,555,558,561,564,567,570,574,577,580,583,586,589,592,595,598,602,605,608,611,614,617,620,623,626,629,632,635,638,641,644,647,650,653,656,659,662,665,668,671,674,677,680,683,686,689,692,695,698,701,704,707,710,713,715,718,721,724,727,730,733,735,738,741,744,747,749,752,755,758,760,763,766,769,771,774,777,779,782,785,787,790,793,795,798,800,803,806,808,811,813,816,818,821,823,826,828,831,833,835,838,840,843,845,847,850,852,855,857,859,861,864,866,868,870,873,875,877,879,881,884,886,888,890,892,894,896,898,900,902,904,906,908,910,912,914,916,918,920,922,924,926,927,929,931,933,935,936,938,940,941,943,945,946,948,950,951,953,954,956,958,959,961,962,964,965,966,968,969,971,972,973,975,976,977,979,980,981,982,984,985,986,987,988,989,990,992,993,994,995,996,997,998,999,1000,1000,1001,1002,1003,1004,1005,1006,1006,1007,1008,1009,1009,1010,1011,1011,1012,1013,1013,1014,1014,1015,1015,1016,1016,1017,1017,1018,1018,1019,1019,1019,1020,1020,1020,1021,1021,1021,1021,1022,1022,1022,1022,1022,1022,1022,1022,1022,1022,1023,1022,1022,1022,1022,1022,1022,1022,1022,1022,1022,1021,1021,1021,1021,1020,1020,1020,1019,1019,1019,1018,1018,1017,1017,1016,1016,1015,1015,1014,1014,1013,1013,1012,1011,1011,1010,1009,1009,1008,1007,1006,1006,1005,1004,1003,1002,1001,1000,1000,999,998,997,996,995,994,993,992,990,989,988,987,986,985,984,982,981,980,979,977,976,975,973,972,971,969,968,966,965,964,962,961,959,958,956,954,953,951,950,948,946,945,943,941,940,938,936,935,933,931,929,927,926,924,922,920,918,916,914,912,910,908,906,904,902,900,898,896,894,892,890,888,886,884,881,879,877,875,873,870,868,866,864,861,859,857,855,852,850,847,845,843,840,838,835,833,831,828,826,823,821,818,816,813,811,808,806,803,800,798,795,793,790,787,785,782,779,777,774,771,769,766,763,760,758,755,752,749,747,744,741,738,735,733,730,727,724,721,718,715,713,710,707,704,701,698,695,692,689,686,683,680,677,674,671,668,665,662,659,656,653,650,647,644,641,638,635,632,629,626,623,620,617,614,611,608,605,602,598,595,592,589,586,583,580,577,574,570,567,564,561,558,555,552,549,545,542,539,536,533,530,527,524,520,517,514,511,508,505,502,498,495,492,489,486,483,480,477,473,470,467,464,461,458,455,452,448,445,442,439,436,433,430,427,424,420,417,414,411,408,405,402,399,396,393,390,387,384,381,378,375,372,369,366,363,360,357,354,351,348,345,342,339,336,333,330,327,324,321,318,315,312,309,307,304,301,298,295,292,289,287,284,281,278,275,273,270,267,264,262,259,256,253,251,248,245,243,240,237,235,232,229,227,224,222,219,216,214,211,209,206,204,201,199,196,194,191,189,187,184,182,179,177,175,172,170,167,165,163,161,158,156,154,152,149,147,145,143,141,138,136,134,132,130,128,126,124,122,120,118,116,114,112,110,108,106,104,102,100,98,96,95,93,91,89,87,86,84,82,81,79,77,76,74,72,71,69,68,66,64,63,61,60,58,57,56,54,53,51,50,49,47,46,45,43,42,41,40,38,37,36,35,34,33,32,30,29,28,27,26,25,24,23,22,22,21,20,19,18,17,16,16,15,14,13,13,12,11,11,10,9,9,8,8,7,7,6,6,5,5,4,4,3,3,3,2,2,2,1,1,1,1,0,0,0,0,0,0,0,0,0,0};

const uint16_t Synthesizer::SawtoothTone[] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80,81,82,83,84,85,86,87,88,89,90,91,92,93,94,95,96,97,98,99,100,101,102,103,104,105,106,107,108,109,110,111,112,113,114,115,116,117,118,119,120,121,122,123,124,125,126,127,128,129,130,131,132,133,134,135,136,137,138,139,140,141,142,143,144,145,146,147,148,149,150,151,152,153,154,155,156,157,158,159,160,161,162,163,164,165,166,167,168,169,170,171,172,173,174,175,176,177,178,179,180,181,182,183,184,185,186,187,188,189,190,191,192,193,194,195,196,197,198,199,200,201,202,203,204,205,206,207,208,209,210,211,212,213,214,215,216,217,218,219,220,221,222,223,224,225,226,227,228,229,230,231,232,233,234,235,236,237,238,239,240,241,242,243,244,245,246,247,248,249,250,251,252,253,254,255,256,257,258,259,260,261,262,263,264,265,266,267,268,269,270,271,272,273,274,275,276,277,278,279,280,281,282,283,284,285,286,287,288,289,290,291,292,293,294,295,296,297,298,299,300,301,302,303,304,305,306,307,308,309,310,311,312,313,314,315,316,317,318,319,320,321,322,323,324,325,326,327,328,329,330,331,332,333,334,335,336,337,338,339,340,341,342,343,344,345,346,347,348,349,350,351,352,353,354,355,356,357,358,359,360,361,362,363,364,365,366,367,368,369,370,371,372,373,374,375,376,377,378,379,380,381,382,383,384,385,386,387,388,389,390,391,392,393,394,395,396,397,398,399,400,401,402,403,404,405,406,407,408,409,410,411,412,413,414,415,416,417,418,419,420,421,422,423,424,425,426,427,428,429,430,431,432,433,434,435,436,437,438,439,440,441,442,443,444,445,446,447,448,449,450,451,452,453,454,455,456,457,458,459,460,461,462,463,464,465,466,467,468,469,470,471,472,473,474,475,476,477,478,479,480,481,482,483,484,485,486,487,488,489,490,491,492,493,494,495,496,497,498,499,500,501,502,503,504,505,506,507,508,509,510,511,512,513,514,515,516,517,518,519,520,521,522,523,524,525,526,527,528,529,530,531,532,533,534,535,536,537,538,539,540,541,542,543,544,545,546,547,548,549,550,551,552,553,554,555,556,557,558,559,560,561,562,563,564,565,566,567,568,569,570,571,572,573,574,575,576,577,578,579,580,581,582,583,584,585,586,587,588,589,590,591,592,593,594,595,596,597,598,599,600,601,602,603,604,605,606,607,608,609,610,611,612,613,614,615,616,617,618,619,620,621,622,623,624,625,626,627,628,629,630,631,632,633,634,635,636,637,638,639,640,641,642,643,644,645,646,647,648,649,650,651,652,653,654,655,656,657,658,659,660,661,662,663,664,665,666,667,668,669,670,671,672,673,674,675,676,677,678,679,680,681,682,683,684,685,686,687,688,689,690,691,692,693,694,695,696,697,698,699,700,701,702,703,704,705,706,707,708,709,710,711,712,713,714,715,716,717,718,719,720,721,722,723,724,725,726,727,728,729,730,731,732,733,734,735,736,737,738,739,740,741,742,743,744,745,746,747,748,749,750,751,752,753,754,755,756,757,758,759,760,761,762,763,764,765,766,767,768,769,770,771,772,773,774,775,776,777,778,779,780,781,782,783,784,785,786,787,788,789,790,791,792,793,794,795,796,797,798,799,800,801,802,803,804,805,806,807,808,809,810,811,812,813,814,815,816,817,818,819,820,821,822,823,824,825,826,827,828,829,830,831,832,833,834,835,836,837,838,839,840,841,842,843,844,845,846,847,848,849,850,851,852,853,854,855,856,857,858,859,860,861,862,863,864,865,866,867,868,869,870,871,872,873,874,875,876,877,878,879,880,881,882,883,884,885,886,887,888,889,890,891,892,893,894,895,896,897,898,899,900,901,902,903,904,905,906,907,908,909,910,911,912,913,914,915,916,917,918,919,920,921,922,923,924,925,926,927,928,929,930,931,932,933,934,935,936,937,938,939,940,941,942,943,944,945,946,947,948,949,950,951,952,953,954,955,956,957,958,959,960,961,962,963,964,965,966,967,968,969,970,971,972,973,974,975,976,977,978,979,980,981,982,983,984,985,986,987,988,989,990,991,992,993,994,995,996,997,998,999,1000,1001,1002,1003,1004,1005,1006,1007,1008,1009,1010,1011,1012,1013,1014,1015,1016,1017,1018,1019,1020,1021,1022,1023};

const uint16_t Synthesizer::SquareWaveTone[] = {1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
/*
 * Simple internal helper funtion that creates a fiber within the givien Synthesizer to handle playback
 */
static Synthesizer *launching = NULL;
void begin_playback()
{
    if (launching)
        launching->generate(-1);
}

/**
  * Class definition for a Synthesizer.
  * A Synthesizer generates a tone waveform based on a number of overlapping waveforms.
  */
Synthesizer::Synthesizer(int sampleRate) : output(*this)
{
    this->bufferSize = 512;
    this->samplePeriodNs = 1000000000 / sampleRate;
    this->setVolume(1024);
    this->active = false;
    this->synchronous = false;
    this->bytesWritten = 0;
    this->tonePrint = Synthesizer::SquareWaveTone;
    this->status |= DEVICE_COMPONENT_STATUS_IDLE_TICK;
}

/**
 * Implement this function to receive a callback when the device is idling.
 */
void Synthesizer::idleCallback()
{
    if (bytesWritten && !synchronous && !active && output.canPull(bytesWritten))
    {
        buffer.truncate(bytesWritten);
        output.pullRequest();
        bytesWritten = 0;
    }
}


/**
  * Define the central frequency of this synthesizer
  */
int Synthesizer::setFrequency(float frequency)
{
    return setFrequency(frequency, 0);
}

/**
 * Define the central frequency of this synthesizer.
 * Takes effect immediately, and automatically stops the tone after the given period.
 * @frequency The frequency, in Hz to generate.
 * @period The period, in ms, to play the frequency.
 */
int Synthesizer::setFrequency(float frequency, int period)
{
    // If another fiber is already actively using this resource, we can't service this request.
    if (synchronous)
        return DEVICE_BUSY;

    // record our new intended frequency.
    newPeriodNs = frequency == 0.0 ? 0 : (uint32_t) (1000000000.0f / frequency);

    if (period == 0)
    {
        // We've been asked to play a new tone in the background.
        // If a tone is already playing in the background, we only need to update frequency (already done above). Otherwise also launch a playout fiber.
        if(!active)
        {
            active = true;
            launching = this;
            create_fiber(begin_playback);
        }
    }
    else
    {
        // We've been asked to playout a new note synchronously. Record the period of playback, and start creation of the sample content.
        synchronous = true;
        generate(1000 * period);
        synchronous = false;
    }

    return DEVICE_OK;
}

/**
 * Destructor.
 * Removes all resources held by the instance.
 */
Synthesizer::~Synthesizer()
{
}

/**
 * Creates the next audio buffer, and attmepts to queue this on the output stream.
 */
void Synthesizer::generate(int playoutTimeUs)
{
    int periodNs = newPeriodNs;
    int position = 0;

    int toneDelta;          // the number of samples within out tone print that we increment for each playout sample.
    int toneSigma;          // the fraction of samples within our tone print (*1000) that we increment for each playout sample.

    float toneRate = periodNs == 0 ? 0 : ((float)samplePeriodNs * (float) TONE_WIDTH) / (float) periodNs;
    toneDelta = (int) toneRate;
    toneSigma = (int) ((toneRate - (float)toneDelta) * 1000.0f);

    int sigma = 0;
    int playoutSamples = determineSampleCount(playoutTimeUs);

    while(playoutSamples != 0)
    {
        if (bytesWritten == 0)
            buffer = ManagedBuffer(bufferSize);

        uint16_t *ptr = (uint16_t *) &buffer[bytesWritten];

        while(bytesWritten < bufferSize)
        {
            *ptr = periodNs > 0 ? (((*(tonePrint + position)) * amplitude) >> 10) : 0;
            bytesWritten += 2;
            ptr++;

            position += toneDelta;
            sigma += toneSigma;

            if (playoutSamples >= 0)
                playoutSamples--;

            if (sigma > 1000)
            {
                sigma -= 1000;
                position++;
            }

            if (position >= TONE_WIDTH)
            {
                position -= TONE_WIDTH;
#ifdef SYNTHESIZER_SIGMA_RESET
                sigma = 0;
#endif
                if (periodNs != newPeriodNs)
                {
                    periodNs = newPeriodNs;

                    toneRate = periodNs == 0 ? 0 : ((float)samplePeriodNs * (float) TONE_WIDTH) / (float) periodNs;
                    toneDelta = (int) toneRate;
                    toneSigma = (int) ((toneRate - (float)toneDelta) * 1000.0f);
                    playoutSamples = determineSampleCount(playoutTimeUs);

                    position = 0;
                    sigma = 0;
                }
            }

            if (playoutSamples == 0)
                return;
        }

        bytesWritten = 0;
        output.pullRequest();

        // There's now space for another buffer. If we're generating asynchronously and a synchronous request comes in, give control to that fiber.
        if (playoutTimeUs < 0 && synchronous)
        {
            active = false;
            return;
        }
    }
}

/**
* Define the volume of the wave to generate.
* @param volume The new output volume, in the range 0..1024
*/
int Synthesizer::setVolume(int volume)
{
    if (volume < 0 || volume > 1024)
        return DEVICE_INVALID_PARAMETER;

    amplitude = volume;

    return DEVICE_OK;
}

/**
* Define the size of the audio buffer to hold. The larger the buffer, the lower the CPU overhead, but the longer the delay.
* @param size The new bufer size to use, in bytes.
* @return DEVICE_OK on success, or DEVICE_INVALID_PARAMETER
*/
int Synthesizer::setBufferSize(int size)
{
    if (bufferSize <= 0)
        return DEVICE_INVALID_PARAMETER;

    this->bufferSize = size;
    return DEVICE_OK;
}

/**
 * Provide the next available ManagedBuffer to our downstream caller, if available.
 */
ManagedBuffer Synthesizer::pull()
{
    return buffer;
}

/**
 * Determine the sample rate currently in use by this Synthesizer.
 * @return the current sample rate, in Hz.
 */
int Synthesizer::getSampleRate()
{
    return 1000000000 / samplePeriodNs;
}

/**
 * Change the sample rate used by this Synthesizer,
 * @param frequency The new sample rate, in Hz.
 * @return DEVICE_OK on success.
 */
int Synthesizer::setSampleRate(int sampleRate)
{
    this->samplePeriodNs = 1000000000 / sampleRate;
    return DEVICE_OK;
}

/**
 * Defines the tone to generate.
 * @param the tone print to use with this synthesizer.
 * Examples include:
 *
 * Synthesizer::SineTone
 * Synthesizer::SawtoothTone
 * Synthesizer::SquareWaveTone
 */
void Synthesizer::setTone(const uint16_t *tonePrint)
{
    this->tonePrint = tonePrint;
}

/**
 * Determine the number of samples required for the given playout time.
 *
 * @param playoutTimeUs The playout time (in microseconds)
 * @return The number if samples required to play for the given amount fo time
 * (at the currently defined sample rate)
 */
int Synthesizer::determineSampleCount(int playoutTimeUs)
{
    if (playoutTimeUs < 0)
        return -1;

    int a = (playoutTimeUs / 1000) * 1000;
    int b = (playoutTimeUs % 1000);

    return ((a / samplePeriodNs) * 1000) + ((1000 * b) / samplePeriodNs);
}

