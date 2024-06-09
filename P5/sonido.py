# Realizado por: Claudia de la Vieja Lafuente

# --------------------------------------------------------------- #
import numpy as np
from scipy.io import wavfile
import matplotlib.pyplot as plt
import scipy.signal as signal
import wave 
from pydub import AudioSegment
from scipy.signal import butter, sosfiltfilt

# --------------------------------------------------------------- #

# Ejercicio 1

# Cargar archivos .wav
Fs, sen = wavfile.read('./nombre.wav')  # Ruta del archivo con la señal
sen = sen.astype(float)
t = np.linspace(0, len(sen) / Fs, len(sen), endpoint=False)  # Asegura misma longitud

Fs2, signal2 = wavfile.read('./apellido.wav')  # Ruta del archivo con la señal
signal2 = signal2.astype(float)
t2 = np.linspace(0, len(signal2) / Fs2, len(signal2), endpoint=False)  # Asegura misma longitud

# --------------------------------------------------------------- #

# Ejercicio 2

# Mostrar gráficas
plt.figure()
plt.plot(t, sen, color='lightblue', label='Claudia')
plt.title('Nombre - Claudia')
plt.xlabel('Tiempo (s)')
plt.ylabel('Amplitud (Hz)')
plt.grid()
plt.legend()

plt.figure()
plt.plot(t2, signal2, color='lightblue', label='de la Vieja Lafuente')
plt.title('Apellido - de la Vieja Lafuente')
plt.xlabel('Tiempo (s)')
plt.ylabel('Amplitud (Hz)')
plt.grid()
plt.legend()

plt.show()

# --------------------------------------------------------------- #

# Ejercicio 3

# Información del primer archivo
signalAr = wave.open('./nombre.wav', 'r')

print("Nombre - Claudia")
print("\n")
print("Número de canales -> ", signalAr.getnchannels())
print("Ancho -> ", signalAr.getsampwidth())
print("Frame rate -> ", signalAr.getframerate())
print("Número de frames -> ", signalAr.getnframes())
print("Parámetros -> ", signalAr.getparams())

signalAr.close()

print("\n")
print("------------------------------------------------------")
print("\n")

# Información del segundo archivo
signalAl = wave.open('./apellido.wav', 'r')

print("Apellido - de la Vieja Lafuente")
print("\n")
print("Número de canales -> ", signalAl.getnchannels())
print("Ancho -> ", signalAl.getsampwidth())
print("Frame rate -> ", signalAl.getframerate())
print("Número de frames -> ", signalAl.getnframes())
print("Parámetros -> ", signalAl.getparams())

signalAl.close()

print("\n")
print("------------------------------------------------------")
print("\n")

# --------------------------------------------------------------- #

# Ejercicio 4

# Cargar archivos de audio
audio1 = AudioSegment.from_wav("./nombre.wav")
audio2 = AudioSegment.from_wav("./apellido.wav")

# Concatenar los audios
audio_concatenado = audio2 +  audio1

# Guardar el audio concatenado en un nuevo archivo
audio_concatenado.export("./sonido_concatenado.wav", format="wav")

# -------------------------------------------------------------- #

# Ejercicio 5

# Cargar el archivo de audio concatenado
Fs_concatenado, sen_concatenada = wavfile.read("./sonido_concatenado.wav")

# Calcular el tiempo correspondiente a cada muestra
t_concatenado = np.arange(len(sen_concatenada)) / Fs_concatenado

# Mostrar gráfica de la forma de onda de la señal concatenada
plt.plot(t_concatenado, sen_concatenada, color='lightblue')
plt.title('Forma de onda del audio concatenado')
plt.xlabel('Tiempo (s)')
plt.ylabel('Amplitud')
plt.grid()
plt.show()

# -------------------------------------------------------------- #

# Ejercicio 6

# Cargar el archivo de audio concatenado
Fs_concatenado, sen_concatenada = wavfile.read("./sonido_concatenado.wav")

# Verificar la frecuencia de muestreo
print("Frecuencia de muestreo:", Fs_concatenado)

# Calcular el tiempo correspondiente a cada muestra
t_concatenado = np.arange(len(sen_concatenada)) / Fs_concatenado

# Definir las frecuencias de corte deseadas en Hz
lowcut = 10000  # Frecuencia de corte inferior en Hz
highcut = 10000  # Frecuencia de corte superior en Hz

# Verificar que las frecuencias de corte estén en el rango correcto
assert 0 < lowcut < Fs_concatenado / 2, "Frecuencia de corte inferior fuera de rango"
assert 0 < highcut < Fs_concatenado / 2, "Frecuencia de corte superior fuera de rango"

# Convertir las frecuencias de corte a frecuencias normalizadas
nyquist_freq = 0.5 * Fs_concatenado  # Frecuencia de Nyquist
lowcut_norm = lowcut / nyquist_freq  # Frecuencia de corte inferior normalizada
highcut_norm = highcut / nyquist_freq  # Frecuencia de corte superior normalizada

# Crear filtro pasa bajo
sos_low = butter(10, lowcut_norm, btype='low', output='sos')

# Aplicar filtro pasa bajo
sen_filtrada_low = sosfiltfilt(sos_low, sen_concatenada)

# Crear filtro pasa alto
sos_high = butter(10, highcut_norm, btype='high', output='sos')

# Aplicar filtro pasa alto
sen_filtrada = sosfiltfilt(sos_high, sen_filtrada_low)

# Calcular el tiempo correspondiente a cada muestra
t_filtrado = np.arange(len(sen_filtrada)) / Fs_concatenado

# Mostrar gráfica de la forma de onda del audio filtrado
plt.plot(t_filtrado, sen_filtrada, color='lightblue')
plt.title('Forma de onda del audio filtrado')
plt.xlabel('Tiempo (s)')
plt.ylabel('Amplitud')
plt.grid()
plt.show()

# -------------------------------------------------------------- #

# Ejercicio 7

# Generar archivo de salida

output_file = "mezcla.wav"
wavfile.write(output_file, Fs_concatenado, sen_filtrada)

# -------------------------------------------------------------- #

# Ejercicio 8

Fs_nuevo, sen_nuevo = wavfile.read("mezcla.wav")

# Convertir la señal de audio a un objeto AudioSegment de PyDub
audio_nuevo = AudioSegment.from_wav("mezcla.wav")

# Obtener la información de formato del objeto AudioSegment
channels = audio_nuevo.channels
sample_width = audio_nuevo.sample_width
frame_rate = audio_nuevo.frame_rate

# Asegurarse de que el formato del archivo cargado sea el mismo que el del objeto AudioSegment
sen_nuevo = sen_nuevo.astype(audio_nuevo.array_type)

# Crear un nuevo objeto AudioSegment con el formato correcto
audio_nuevo = AudioSegment(sen_nuevo.tobytes(), frame_rate=frame_rate, sample_width=sample_width, channels=channels)

# Aplicar un efecto de eco a la señal de audio (ejemplo de eco con retraso de 0.5 segundos y atenuación de -10 dB)
audio_nuevo_eco = audio_nuevo.overlay(audio_nuevo, position=500)

# Darle la vuelta a la señal de audio
audio_nuevo_alreves = audio_nuevo.reverse()

# Almacenar la señal obtenida como un archivo WAV denominado "alreves.wav"
audio_nuevo_alreves.export("alreves.wav", format="wav")