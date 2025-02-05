using System;
using System.Runtime.InteropServices;

namespace WeDo2Sample
{
    public class DeviceEnumerator : TextContentEnumerator
    {
        void Awake()
        {
            DeviceController.Instance.OnScanCompleted += Enumerate;
        }

        /// <summary>
        /// 検出されたデバイスを列挙する.
        /// </summary>
        /// <param name="result">デバイスIDの配列を指すポインタ.</param>
        /// <param name="size">配列のサイズ.</param>
        public void Enumerate(IntPtr result, uint size)
        {
            Clear();
            for (int i = 0; i < size; i++)
            {
                IntPtr ptr = Marshal.ReadIntPtr(result, i * Marshal.SizeOf(typeof(IntPtr)));
                string deviceId = Marshal.PtrToStringAuto(ptr);
                Push(deviceId);
            }
        }
    }
}
