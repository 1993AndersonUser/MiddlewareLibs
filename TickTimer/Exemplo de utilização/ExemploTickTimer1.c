
TickTimer Timer1;

void ToggleLed(void)
{
	LED1 = ~LED1;
}

void AppInit(void)
{
	TickTimerSet(&Timer1, 500);
}

void App(void)
{
	if (TickTimerExpired(&Timer1))
	{
		TickTimerRestart();
		ToggleLed();
	}
}