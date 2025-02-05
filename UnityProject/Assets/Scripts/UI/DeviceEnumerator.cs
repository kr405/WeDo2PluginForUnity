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
        /// ���o���ꂽ�f�o�C�X��񋓂���.
        /// </summary>
        /// <param name="result">�f�o�C�XID�̔z����w���|�C���^.</param>
        /// <param name="size">�z��̃T�C�Y.</param>
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
