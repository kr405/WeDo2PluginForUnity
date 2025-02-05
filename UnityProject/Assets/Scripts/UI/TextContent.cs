using TMPro;

namespace WeDo2Sample
{
    public class TextContent : TextUI
    {
        public uint Number { get; set; }

        protected override void Awake()
        {
            tMPro = GetComponentInChildren<TextMeshProUGUI>();
        }
    }
}
