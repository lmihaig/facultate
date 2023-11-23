import alsaaudio as aa
import wave
import pyaudio
from struct import unpack
import numpy as np
from rgbmatrix import RGBMatrix, RGBMatrixOptions
import sys


def calculate_levels(data, chunk):
    # aplica transformarea FTT pe toate datele matricii la momentul actual
    data = unpack("%dh" % (len(data) / 2), data)
    data = np.array(data, dtype="h")
    fourier = np.fft.rfft(data)
    fourier = np.delete(fourier, len(fourier) - 1)
    power = np.log10(np.abs(fourier)) ** 2
    power = np.reshape(power, (32, int(chunk / 32)))
    matrix = np.int_(np.average(power, axis=1))
    return matrix


def display_loop(matrix):
    Dmatrix.Clear()
    for y in range(32):
        for x in range(matrix[y]):
            # default alb
            r, g, b = 255, 255, 255
            if x < 16:
                # verde
                r, g, b = 0, 132, 80
            elif x < 28:
                # galben
                r, g, b = 239, 183, 0
            else:
                # rosu
                r, g, b = 184, 29, 19
            Dmatrix.SetPixel(y, x, r, g, b)
            Dmatrix.SetPixel(y, x - 1, r, g, b)

    return None


def spectrum_fisier(path):
    wavfile = wave.open(path)
    sample_rate = wavfile.getframerate()
    # obiectul de output folosit pentru a reda sunetul pentru a fi auzit in timp real
    output = aa.PCM(aa.PCM_PLAYBACK, aa.PCM_NORMAL)
    output.setchannels(2)
    output.setrate(sample_rate)
    output.setformat(aa.PCM_FORMAT_S16_LE)
    output.setperiodsize(chunk)

    data = wavfile.readframes(chunk)
    while data != "":
        output.write(data)
        matrix = calculate_levels(data, chunk)
        display_loop(matrix)
        data = wavfile.readframes(chunk)

    return None


def spectrum_microfon():
    no_channels = 1
    sample_rate = 44100
    device = 2
    p = pyaudio.PyAudio()
    stream = p.open(
        format=pyaudio.paInt16,
        channels=no_channels,
        rate=sample_rate,
        input=True,
        frames_per_buffer=chunk,
        input_device_index=device,
    )

    # loop infinit care citeste audio data de la microfon si updateaza matricea cu noile informatii
    while 1:
        try:
            data = stream.read(chunk)
            matrix = calculate_levels(data, chunk)
            Dmatrix.Clear()
            display_loop(matrix)
        except KeyboardInterrupt:
            print("Se opreste...")
            stream.stop_stream()
            stream.close()
            p.terminate()
            sys.exit(1)
        except Exception as e:
            print(e)
            print("Eroare...")
            stream.stop_stream()
            stream.close()
            p.terminate()
            sys.exit(1)

    return None


# interfata pentru a comunica cu matricea de leduri si a updata pixelii acestia
options = RGBMatrixOptions()
options.rows = 16
options.cols = 32
options.chain_length = 1
options.parallel = 1
options.hardware_mapping = "adafruit-hat"
Dmatrix = RGBMatrix(options=options)
Dmatrix.Clear()

# reprezinta dimensiunea portiei pe care o citim din bufferul audio
chunk = 16 * 32

# reprezentarea doi dimensionala a matricei de LEDuri
matrix = [0 for _ in range(32)]

if __name__ == "__main__":
    if len(sys.argv) == 2:
        if sys.argv[1] == "mic":
            print("CTRL+C pentru a termina executia")
            spectrum_microfon()
        else:
            spectrum_fisier(sys.argv[1])
    else:
        print(
            f"Eroare utilizare. Utilizare corecta: {sys.argv[0]} <optiune> unde optiune = mic SAU calea spre fisierul audio dorit."
        )
