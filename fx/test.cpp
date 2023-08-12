#include "AudioFile.h"
#include <string>
#include <vector>
#include <chrono>
#include <tgmath.h>

#include "Compressor.hpp"
#include "Delay.hpp"
#include "Common.hpp"
int main(){
    afx_common::CommonParams common_params(128, 2, 44100.0f);
    AudioFile<float> input_stream;
    std::string output_file_name = "eg002";
    input_stream.load(output_file_name + ".wav");

    const int number_of_buffers = input_stream.getNumSamplesPerChannel() / common_params.buffer_length();
    AudioFile<float> output_stream;
    AudioFile<float>::AudioBuffer output_buffer;
    output_buffer.resize(common_params.number_of_channels());
    output_buffer[0].resize(number_of_buffers * common_params.buffer_length());
    output_buffer[1].resize(number_of_buffers * common_params.buffer_length());
    std::vector<float> buffer(common_params.buffer_size());

    Compressor compressor(common_params);
    Delay delay(common_params);
    
    for(auto i = 0; i < number_of_buffers; i++){
        for(auto j = 0; j < common_params.buffer_length(); j++){
            for(auto k = 0; k < common_params.number_of_channels(); k++){
                buffer[common_params.number_of_channels() * j + k] = input_stream.samples[k][j + i * common_params.buffer_length()];
            }
        }

        compressor.compress(&buffer[0]);
        delay.delay(&buffer[0]);
        
        for(auto j = 0; j < common_params.buffer_length(); j++){
            for(auto k = 0; k < common_params.number_of_channels(); k++){
                output_buffer[k][j + i * common_params.buffer_length()] = buffer[common_params.number_of_channels() * j + k];
            }
        }
    }
    
    output_stream.setAudioBuffer(output_buffer);
    output_stream.setNumSamplesPerChannel(number_of_buffers * common_params.buffer_length());
    output_stream.setNumChannels(common_params.number_of_channels());
    output_stream.setBitDepth(16);
    output_stream.setSampleRate(44100);
    output_stream.save(output_file_name + "_cppout.wav");
    
    return 0;
}