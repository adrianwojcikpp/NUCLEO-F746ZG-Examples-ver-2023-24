import numpy as np
import matplotlib.pyplot as plt
from dataclasses import dataclass
from csnake import CodeWriter, Variable

@dataclass
class SineWave:
    Amplitude: float
    Phase: float
    Frequency: float
    Mean: float
    SampleTime: float

def main():
    sine_wave = SineWave(Amplitude=1000.0, Phase=0.0, Frequency=10.0, Mean=1000.0, SampleTime=0.001)   
    time = sine_wave.SampleTime * np.linspace(0, 99, 100)  
    values = (sine_wave.Amplitude)*np.sin(2*np.pi*sine_wave.Frequency*time + sine_wave.Phase) + sine_wave.Mean
    dac_reg = (4095/3300)*values
    dac_reg = dac_reg.astype(np.int16)

    c_array = Variable("sine_wave_buffer", primitive="uint16_t", value=dac_reg)

    cw_src = CodeWriter()
    cw_src.include("<stdint.h>")
    cw_src.add_variable_initialization(c_array)

    cw_inc = CodeWriter()
    cw_inc.include("<stdint.h>")
    cw_inc.add_define("SINE_WAVE_SIZE", 100)
    cw_inc.add_variable_declaration(c_array, extern = True)

    with open("../Components/Src/sine_wave_buffer.c", "w") as src:
        src.write("// PYTHON GENERATED FILE\n")
        src.write(str(cw_src))

    with open("../Components/Inc/sine_wave_buffer.h", "w") as inc:
        inc.write("// PYTHON GENERATED FILE\n")
        inc.write(str(cw_inc))

    plt.figure(figsize=(8, 4))
    plt.plot(time, values, label='Sine Wave')
    plt.title('Sine Wave')
    plt.xlabel('Time [s]')
    plt.ylabel('Voltage [mV]')
    plt.legend()
    plt.grid(True)
    plt.show()

if __name__ == "__main__":
    main()
