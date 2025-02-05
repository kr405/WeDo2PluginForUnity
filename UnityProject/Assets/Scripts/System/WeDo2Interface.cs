using System;
using System.Runtime.InteropServices;

namespace WeDo2Sample
{
    public static class WeDo2Interface
    {
        const string PLUGIN_NAME = "WeDo2Plugin";

        [DllImport(PLUGIN_NAME, EntryPoint = "WeDo2Plugin_Scan")]
        public static extern void Scan(IntPtr onScanCompleted);

        [DllImport(PLUGIN_NAME, EntryPoint = "WeDo2Plugin_Connect")]
        public static extern void Connect(uint index, IntPtr onRequestCompleted);

        [DllImport(PLUGIN_NAME, EntryPoint = "WeDo2Plugin_Disconnect")]
        public static extern void Disconnect(IntPtr onRequestCompleted);

        [DllImport(PLUGIN_NAME, EntryPoint = "WeDo2Plugin_SetLed")]
        public static extern void SetLed(uint rgb, IntPtr onRequestCompleted);

        [DllImport(PLUGIN_NAME, EntryPoint = "WeDo2Plugin_PlayNote")]
        public static extern void PlayNote(ushort note, ushort milliseconds, IntPtr onRequestCompleted);

        [DllImport(PLUGIN_NAME, EntryPoint = "WeDo2Plugin_StopNote")]
        public static extern void StopNote(IntPtr onRequestCompleted);

        [DllImport(PLUGIN_NAME, EntryPoint = "WeDo2Plugin_TurnOnMotor")]
        public static extern void TurnOnMotor(byte port, sbyte direction, byte power, IntPtr onRequestCompleted);

        [DllImport(PLUGIN_NAME, EntryPoint = "WeDo2Plugin_Distance")]
        public static extern byte Distance();

        [DllImport(PLUGIN_NAME, EntryPoint = "WeDo2Plugin_TiltX")]
        public static extern sbyte TiltX();

        [DllImport(PLUGIN_NAME, EntryPoint = "WeDo2Plugin_TiltY")]
        public static extern sbyte TiltY();

        [DllImport(PLUGIN_NAME, EntryPoint = "WeDo2Plugin_IsConnected")]
        public static extern bool IsConnected();
    }
}
