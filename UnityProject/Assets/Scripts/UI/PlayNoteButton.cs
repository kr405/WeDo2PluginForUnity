using UnityEngine;

namespace WeDo2Sample
{
    public class PlayNoteButton : Button
    {
        [SerializeField, Range(25, 125)] ushort m_note;
        [SerializeField] ushort m_duration;

        protected override void OnClick()
        {
            DeviceController.Instance.PlayNote(m_note, m_duration);
        }
    }
}