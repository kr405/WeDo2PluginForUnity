using TMPro;

namespace WeDo2Sample
{
    public abstract class Button : TextUI
    {
        protected UnityEngine.UI.Button button;

        protected override void Awake()
        {
            tMPro = GetComponentInChildren<TextMeshProUGUI>();
            button = GetComponent<UnityEngine.UI.Button>();
            button.onClick.AddListener(OnClick);
        }

        /// <summary>
        /// クリック時に呼び出される処理.
        /// </summary>
        protected abstract void OnClick();
    }
}
