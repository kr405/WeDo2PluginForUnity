using UnityEngine;

namespace WeDo2Sample
{
    public class TextContentEnumerator : MonoBehaviour
    {
        [SerializeField] TextContent content;

        uint counter = 0;

        /// <summary>
        /// �e�L�X�g��񋓂���.
        /// </summary>
        /// <param name="texts">�e�L�X�g�̔z��.</param>
        public virtual void Enumerate(string[] texts)
        {
            Clear();
            foreach (var text in texts)
            {
                Push(text);
            }
        }

        /// <summary>
        /// �񋓂���Ă���e�L�X�g��S�č폜����.
        /// </summary>
        public virtual void Clear()
        {
            var contents = GetComponentsInChildren<TextContent>();
            foreach (var content in contents)
            {
                Remove(content);
            }
        }

        /// <summary>
        /// �V�����e�L�X�g��ǉ�����.
        /// </summary>
        /// <param name="text">�e�L�X�g.</param>
        public virtual void Push(string text)
        {
            var obj = Instantiate(content);
            obj.Text = text;
            obj.transform.SetParent(transform);
            obj.Number = counter;
            counter++;
        }

        /// <summary>
        /// �w�肵���e�L�X�g���폜����.
        /// </summary>
        /// <param name="content">�Ώۂ̃e�L�X�g.</param>
        public virtual void Remove(TextContent content)
        {
            Destroy(content.gameObject);
            counter--;
        }
    }
}


