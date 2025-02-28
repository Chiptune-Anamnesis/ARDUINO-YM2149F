#!/usr/bin/env python3
"""
Converts all WAV files in a specified folder into C-style code arrays,
resampling them to a target sample rate, and writes the generated code
to an output text file.
"""

# ===============================
# USER CONFIGURATION VARIABLES
# ===============================
WAV_FOLDER = "E:\\SoundFonts\\chiptune_soundfont_4.0\\Drums"  # Folder containing your WAV samples
OUTPUT_TEXT_FILE = "E:\SoundFonts\\chiptune_soundfont_4.0\\Drums\\output.txt"                   # File to which the generated C code will be written
OUTPUT_RANGE = (0, 15)                            # Desired quantization range (e.g., 0 to 15)
TARGET_SAMPLE_RATE = 4000                         # Desired sample rate (Hz) for conversion
USE_FIXED_RANGE = True                            # If True, use a fixed normalization range
FIXED_MIN = -8192                                 # Minimum value for fixed-range normalization
FIXED_MAX = 8191                                  # Maximum value for fixed-range normalization
OUTPUT_LENGTH_LIMIT = 2048                        # Maximum number of samples to output (adjust as needed)
ARRAY_TYPE = "uint8_t"                            # Data type for the generated C array
# ===============================

import os
import numpy as np
from scipy.io import wavfile
from scipy.signal import resample
import warnings

# Suppress WAV file non-data chunk warnings
warnings.filterwarnings("ignore", message="Chunk (non-data) not understood, skipping it.")

def convert_pcm_to_array(filename, output_range=OUTPUT_RANGE):
    """
    Reads a WAV file, resamples it to TARGET_SAMPLE_RATE if needed,
    converts its PCM data into a quantized array within the specified
    output range, and returns:
        - A list of quantized integers (limited to OUTPUT_LENGTH_LIMIT samples)
        - The (target) sample rate
        - The number of samples in the converted data
    """
    # Read the WAV file
    sample_rate, data = wavfile.read(filename)
    data = data.astype(np.float32)
    
    # If stereo, take only one channel
    if data.ndim > 1:
        data = data[:, 0]
    
    # Resample if needed
    if sample_rate != TARGET_SAMPLE_RATE:
        new_length = int(len(data) * TARGET_SAMPLE_RATE / sample_rate)
        data = resample(data, new_length)
        sample_rate = TARGET_SAMPLE_RATE
    
    # Normalize the data
    if USE_FIXED_RANGE:
        data_min, data_max = FIXED_MIN, FIXED_MAX
    else:
        data_min, data_max = data.min(), data.max()
    
    if data_max - data_min == 0:
        scaled_data = np.zeros_like(data, dtype=float)
    else:
        scaled_data = (data - data_min) / (data_max - data_min)
    
    # Quantize to the desired output range
    quantized_data = np.round(scaled_data * (output_range[1] - output_range[0])).astype(int)
    quantized_data = np.clip(quantized_data, output_range[0], output_range[1])
    
    # Limit the output length
    if len(quantized_data) > OUTPUT_LENGTH_LIMIT:
        quantized_data = quantized_data[:OUTPUT_LENGTH_LIMIT]
    
    return quantized_data.tolist(), sample_rate, len(quantized_data)

def generate_code_for_sample(array_data, sample_name, sample_rate, count, array_type=ARRAY_TYPE):
    """
    Generates a C-style code snippet for a given sample array.
    The sample data is output horizontally.
    """
    array_str = ", ".join(map(str, array_data))
    code  = f"// Sample: {sample_name}\n"
    code += f"// Sample Rate: {sample_rate} Hz, Sample Count: {count}\n"
    code += f"PROGMEM const {array_type} {sample_name}[] = {{ {array_str} }};\n"
    code += f"const unsigned int {sample_name}_len = {count};\n\n"
    return code

def sanitize_name(filename):
    """
    Converts a filename into a valid C identifier (without extension).
    """
    base = os.path.splitext(filename)[0]
    safe = "".join(c if c.isalnum() else "_" for c in base)
    if safe and safe[0].isdigit():
        safe = "_" + safe
    return safe

def process_folder(wav_folder, output_file):
    """
    Processes each WAV file in the specified folder and writes generated
    C code to the output file.
    """
    all_code = "// Generated sample arrays from WAV files\n\n"
    
    for file in os.listdir(wav_folder):
        if file.lower().endswith(".wav"):
            full_path = os.path.join(wav_folder, file)
            sample_name = sanitize_name(file)
            try:
                array_data, sample_rate, count = convert_pcm_to_array(full_path, OUTPUT_RANGE)
                code = generate_code_for_sample(array_data, sample_name, sample_rate, count)
                all_code += code
                print(f"Processed {file} ({count} samples)")
            except Exception as e:
                print(f"Error processing {file}: {e}")
    
    with open(output_file, "w") as outF:
        outF.write(all_code)
    
    print(f"Output code written to {output_file}")

if __name__ == "__main__":
    process_folder(WAV_FOLDER, OUTPUT_TEXT_FILE)
