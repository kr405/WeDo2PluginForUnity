using TMPro;
using UnityEngine;

namespace WeDo2Sample
{
    public class TextUI : MonoBehaviour
    {
        protected TextMeshProUGUI tMPro;

        public string Text
        {
            get => tMPro.text;
            set => tMPro.text = value;
        }

        protected virtual void Awake()
        {
            tMPro = GetComponent<TextMeshProUGUI>();
        }
    }
}
