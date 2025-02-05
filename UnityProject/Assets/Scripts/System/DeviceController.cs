using System;
using System.Runtime.InteropServices;
using UnityEngine;
using UnityEngine.SceneManagement;

namespace WeDo2Sample
{
    /// <summary>
    /// モーターのポート.
    /// </summary>
    public enum Port
    {
        Right,
        Left,
    }

    /// <summary>
    /// モーターの回転方向.
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
        /// デバイスへのリクエストが完了したときに呼び出す.
        /// </summary>
        /// <param name="successed">リクエストが成功したかどうか.</param>
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
        /// デバイスとの接続状態を通知する.
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
        /// デバイスを検索する.
        /// </summary>
        public void Scan()
        {
            IntPtr callback = Marshal.GetFunctionPointerForDelegate(m_scanCompleted);
            WeDo2Interface.Scan(callback);
        }

        /// <summary>
        /// 選択中のデバイスに接続する.
        /// </summary>
        public void Connect()
        {
            IntPtr callback = Marshal.GetFunctionPointerForDelegate(m_connectRequestCompleted);
            WeDo2Interface.Connect(SelectedDevice, callback);
        }

        /// <summary>
        /// 接続中のデバイスを切断する.
        /// </summary>
        public void Disconnect()
        {
            IntPtr callback = Marshal.GetFunctionPointerForDelegate(m_disconnectRequestCompleted);
            WeDo2Interface.Disconnect(callback);
        }

        /// <summary>
        /// デバイスのライトの色を変更する.
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
        /// ノート（音符）を再生する.
        /// </summary>
        /// <param name="note">ノート番号.</param>
        /// <param name="duration">再生時間(ミリ秒).</param>
        public void PlayNote(ushort note, ushort duration)
        {
            IntPtr callback = Marshal.GetFunctionPointerForDelegate(m_writeRequestCompleted);
            WeDo2Interface.PlayNote(note, duration, callback);
        }

        /// <summary>
        /// ノート（音符）の再生を止める.
        /// </summary>
        public void StopNote()
        {
            IntPtr callback = Marshal.GetFunctionPointerForDelegate(m_writeRequestCompleted);
            WeDo2Interface.StopNote(callback);
        }

        /// <summary>
        /// モーターを動かす.
        /// </summary>
        /// <param name="port">ポート.</param>
        /// <param name="direction">回転方向.</param>
        /// <param name="power">回転力.</param>
        public void TurnOnMotor(Port port, Direction direction, byte power)
        {
            IntPtr callback = Marshal.GetFunctionPointerForDelegate(m_writeRequestCompleted);
            WeDo2Interface.TurnOnMotor((byte)port, (sbyte)direction, power, callback);
        }

        /// <summary>
        /// モーターを止める.
        /// </summary>
        public void StopMotor(Port port)
        {
            IntPtr callback = Marshal.GetFunctionPointerForDelegate(m_writeRequestCompleted);
            WeDo2Interface.TurnOnMotor((byte)port, (sbyte)Direction.Left, 0, callback);
        }
    }
}
