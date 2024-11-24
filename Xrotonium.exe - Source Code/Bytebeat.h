namespace Bytebeat {
	void Bytebeat1(void) {
		HWAVEOUT hwo;
		WAVEFORMATEX wftx = { WAVE_FORMAT_PCM, 1, 16000, 16000, 1, 8, 0 };
		char tbuffer[16000 * 40];
		waveOutOpen(&hwo, WAVE_MAPPER, &wftx, 1, 0, CALLBACK_NULL);
		for (unsigned long t = 0; t < sizeof(tbuffer); t++) {
			tbuffer[t] = static_cast<char>((t/20^t/30)+t);
		}
		WAVEHDR whdr = { tbuffer, sizeof(tbuffer), 0, 0, 0, 0, 0, 0 };
		waveOutPrepareHeader(hwo, &whdr, sizeof(whdr));
		waveOutWrite(hwo, &whdr, sizeof(whdr));
		waveOutUnprepareHeader(hwo, &whdr, sizeof(whdr));
		waveOutClose(hwo);
	}
	
	void Bytebeat2(void) {
		HWAVEOUT hwo;
		WAVEFORMATEX wftx = { WAVE_FORMAT_PCM, 1, 19000, 19000, 1, 8, 0 };
		char tbuffer[19000 * 15];
		waveOutOpen(&hwo, WAVE_MAPPER, &wftx, 1, 0, CALLBACK_NULL);
		for (unsigned long t = 0; t < sizeof(tbuffer); t++) {
			tbuffer[t] = static_cast<char>((t/20+t/50)-t*t);
		}
		WAVEHDR whdr = { tbuffer, sizeof(tbuffer), 0, 0, 0, 0, 0, 0 };
		waveOutPrepareHeader(hwo, &whdr, sizeof(whdr));
		waveOutWrite(hwo, &whdr, sizeof(whdr));
		waveOutUnprepareHeader(hwo, &whdr, sizeof(whdr));
		waveOutClose(hwo);
	}
	
	void Bytebeat3(void) {
		HWAVEOUT hwo;
		WAVEFORMATEX wftx = { WAVE_FORMAT_PCM, 1, 19000, 19000, 1, 8, 0 };
		char tbuffer[19000 * 30];
		waveOutOpen(&hwo, WAVE_MAPPER, &wftx, 1, 0, CALLBACK_NULL);
		for (unsigned long t = 0; t < sizeof(tbuffer); t++) {
			tbuffer[t] = static_cast<char>((t|t>>4|30)*t>>13);
		}
		WAVEHDR whdr = { tbuffer, sizeof(tbuffer), 0, 0, 0, 0, 0, 0 };
		waveOutPrepareHeader(hwo, &whdr, sizeof(whdr));
		waveOutWrite(hwo, &whdr, sizeof(whdr));
		waveOutUnprepareHeader(hwo, &whdr, sizeof(whdr));
		waveOutClose(hwo);
	}
	
	void Bytebeat4(void) {
		HWAVEOUT hwo;
		WAVEFORMATEX wftx = { WAVE_FORMAT_PCM, 1, 16000, 16000, 1, 8, 0 };
		char tbuffer[16000 * 25];
		waveOutOpen(&hwo, WAVE_MAPPER, &wftx, 1, 0, CALLBACK_NULL);
		for (unsigned long t = 0; t < sizeof(tbuffer); t++) {
			tbuffer[t] = static_cast<char>(2*sin(t>>(t%32?4:3)|(t%128?t>>3:t>>3|t>>9)));
		}
		WAVEHDR whdr = { tbuffer, sizeof(tbuffer), 0, 0, 0, 0, 0, 0 };
		waveOutPrepareHeader(hwo, &whdr, sizeof(whdr));
		waveOutWrite(hwo, &whdr, sizeof(whdr));
		waveOutUnprepareHeader(hwo, &whdr, sizeof(whdr));
		waveOutClose(hwo);
	}
	
	void Bytebeat5(void) {
		HWAVEOUT hwo;
		WAVEFORMATEX wftx = { WAVE_FORMAT_PCM, 1, 16000, 16000, 1, 8, 0 };
		char tbuffer[16000 * 35];
		waveOutOpen(&hwo, WAVE_MAPPER, &wftx, 1, 0, CALLBACK_NULL);
		for (unsigned long t = 0; t < sizeof(tbuffer); t++) {
			tbuffer[t] = static_cast<char>((t&7)*(t>>4)*t>>12);
		}
		WAVEHDR whdr = { tbuffer, sizeof(tbuffer), 0, 0, 0, 0, 0, 0 };
		waveOutPrepareHeader(hwo, &whdr, sizeof(whdr));
		waveOutWrite(hwo, &whdr, sizeof(whdr));
		waveOutUnprepareHeader(hwo, &whdr, sizeof(whdr));
		waveOutClose(hwo);
	}
}
