using System;
using System.Runtime.InteropServices;
using UnityEngine;
using UnityEngine.SceneManagement;

namespace WeDo2Sample
{
    /// <summary>
    /// ���[�^�[�̃|�[�g.
    /// </summary>
    public enum Port
    {
        Right,
        Left,
    }

    /// <summary>
    /// ���[�^�[�̉�]����.
    /// </summary>
    public enum Direction
    {
        Right = 1,
        Left = -1,
    }

    public class DeviceController : Singleton<DeviceController>
    {
        public event Action<IntPtr, uint> OnScanCompleted;
        public event Action<bool> OnConnectRequestCompleted;
        public event Action<bool> OnDisconnectRequestCompleted;
        public event Action<bool> OnConnectionStatusChanged;

        Action<IntPtr, uint> m_scanCompleted;
        Action<bool> m_connectRequestCompleted;
        Action<bool> m_disconnectRequestCompleted;
        Action<bool> m_writeRequestCompleted;
        Notification m_notification;
        bool m_wasConnected;

        public uint SelectedDevice { get; set; }

        public bool IsConnected
        {
            get => WeDo2Interface.IsConnected();
        }

        public byte Distance
        {
            get => WeDo2Interface.Distance();
        }

        public sbyte TiltX
        {
            get => WeDo2Interface.TiltX();
        }

        public sbyte TiltY
        {
            get => WeDo2Interface.TiltY();
        }

        protected override void Awake()
        {
            base.Awake();
            m_scanCompleted = (results, size) => { OnScanCompleted(results, size); };
            m_connectRequestCompleted = (successed) => { OnConnectRequestCompleted(successed); };
            m_disconnectRequestCompleted = (successed) => { OnDisconnectRequestCompleted(successed); };
            m_writeRequestCompleted = (successed) => {};

            OnConnectionStatusChanged += NotifyConnectionStauts;
            OnConnectRequestCompleted += RequestCompleted;
            OnDisconnectRequestCompleted += RequestCompleted;
            
            m_notification = FindAnyObjectByType<Notification>();
            SceneManager.sceneUnloaded += scene => Dispose();
        }

        void Update()
        {
            if (m_wasConnected != IsConnected)
            {
                OnConnectionStatusChanged(IsConnected);
                m_wasConnected = IsConnected;
            }
        }

        void OnApplicationQuit()
        {
            Disconnect();
        }

        /// <summary>
        /// �f�o�C�X�ւ̃��N�G�X�g�����������Ƃ��ɌĂяo��.
        /// </summary>
        /// <param name="successed">���N�G�X�g�������������ǂ���.</param>
        void RequestCompleted(bool successed)
        {
            if (successed)
            {
                Debug.Log("Request successed.");
            }
            else
            {
                Debug.Log("Request failed.");
            }
        }

        /// <summary>
        /// �f�o�C�X�Ƃ̐ڑ���Ԃ�ʒm����.
        /// </summary>
        /// <param name="isConnected"></param>
        void NotifyConnectionStauts(bool isConnected)
        {
            if (isConnected)
            {
                m_notification.Notify("Device Connected.");
            }
            else
            {
                m_notification.Notify("Device Disconnected.");
            }
        }

        /// <summary>
        /// �f�o�C�X����������.
        /// </summary>
        public void Scan()
        {
            IntPtr callback = Marshal.GetFunctionPointerForDelegate(m_scanCompleted);
            WeDo2Interface.Scan(callback);
        }

        /// <summary>
        /// �I�𒆂̃f�o�C�X�ɐڑ�����.
        /// </summary>
        public void Connect()
        {
            IntPtr callback = Marshal.GetFunctionPointerForDelegate(m_connectRequestCompleted);
            WeDo2Interface.Connect(SelectedDevice, callback);
        }

        /// <summary>
        /// �ڑ����̃f�o�C�X��ؒf����.
        /// </summary>
        public void Disconnect()
        {
            IntPtr callback = Marshal.GetFunctionPointerForDelegate(m_disconnectRequestCompleted);
            WeDo2Interface.Disconnect(callback);
        }

        /// <summary>
        /// �f�o�C�X�̃��C�g�̐F��ύX����.
        /// </summary>
        /// <param name="hue"></param>
        public void SetLightHue(Color32 hue)
        {
            int rgb = hue.r << 16;
            rgb += hue.g << 8;
            rgb += hue.b;
            IntPtr callback = Marshal.GetFunctionPointerForDelegate(m_writeRequestCompleted);
            WeDo2Interface.SetLed((uint)rgb, callback);
        }

        /// <summary>
        /// �m�[�g�i�����j���Đ�����.
        /// </summary>
        /// <param name="note">�m�[�g�ԍ�.</param>
        /// <param name="duration">�Đ�����(�~���b).</param>
        public void PlayNote(ushort note, ushort duration)
        {
            IntPtr callback = Marshal.GetFunctionPointerForDelegate(m_writeRequestCompleted);
            WeDo2Interface.PlayNote(note, duration, callback);
        }

        /// <summary>
        /// �m�[�g�i�����j�̍Đ����~�߂�.
        /// </summary>
        public void StopNote()
        {
            IntPtr callback = Marshal.GetFunctionPointerForDelegate(m_writeRequestCompleted);
            WeDo2Interface.StopNote(callback);
        }

        /// <summary>
        /// ���[�^�[�𓮂���.
        /// </summary>
        /// <param name="port">�|�[�g.</param>
        /// <param name="direction">��]����.</param>
        /// <param name="power">��]��.</param>
        public void TurnOnMotor(Port port, Direction direction, byte power)
        {
            IntPtr callback = Marshal.GetFunctionPointerForDelegate(m_writeRequestCompleted);
            WeDo2Interface.TurnOnMotor((byte)port, (sbyte)direction, power, callback);
        }

        /// <summary>
        /// ���[�^�[���~�߂�.
        /// </summary>
        public void StopMotor(Port port)
        {
            IntPtr callback = Marshal.GetFunctionPointerForDelegate(m_writeRequestCompleted);
            WeDo2Interface.TurnOnMotor((byte)port, (sbyte)Direction.Left, 0, callback);
        }
    }
}
