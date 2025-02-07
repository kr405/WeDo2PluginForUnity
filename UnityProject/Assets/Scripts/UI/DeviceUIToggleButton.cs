using UnityEngine;

namespace WeDo2Sample
{
    public class DeviceUIToggleButton : ToggleButton
    {
        [SerializeField] GameObject m_deviceUI;

        protected override void Awake()
        {
            base.Awake();
            UpdateUI();
        }

        protected override void OnClick()
        {            
            base.OnClick();
            UpdateUI();
        }

        /// <summary>
        /// UIを更新する.
        /// </summary>
        void UpdateUI()
        {
            Text = isEnabled ? "x" : "=";
            m_deviceUI.SetActive(isEnabled);
        }
    }
}